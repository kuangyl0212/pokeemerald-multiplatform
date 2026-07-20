package com.pokeemerald.experimental;

import android.view.InputDevice;

import java.util.List;

/**
 * 手柄检测纯逻辑。
 *
 * 提取自 PokeEmeraldActivity，便于在不依赖 Android 运行时的情况下做单元测试。
 * 判定规则：任意一个非虚拟设备同时具备 SOURCE_GAMEPAD 或 SOURCE_CLASS_JOYSTICK，
 * 即视为"标准手柄"已连接，应隐藏虚拟按键。
 * 仅 SOURCE_DPAD（如遥控器）不算手柄，避免误隐藏。
 */
final class GamepadDetector {

    private GamepadDetector() {}

    /**
     * 判定给定设备列表中是否存在标准手柄。
     *
     * @param devices 当前所有 InputDevice（可为空列表）
     * @return true 表示应隐藏虚拟按键
     */
    static boolean shouldHideControls(List<InputDevice> devices) {
        if (devices == null || devices.isEmpty()) {
            return false;
        }
        for (InputDevice dev : devices) {
            if (dev == null) continue;
            if (dev.isVirtual()) continue;
            int sources = dev.getSources();
            boolean isGamepad = (sources & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD;
            boolean isJoystick = (sources & InputDevice.SOURCE_CLASS_JOYSTICK) != 0;
            if (isGamepad || isJoystick) {
                return true;
            }
        }
        return false;
    }
}
