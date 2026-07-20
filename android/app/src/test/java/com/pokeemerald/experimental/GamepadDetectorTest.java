package com.pokeemerald.experimental;

import android.view.InputDevice;

import org.junit.Test;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

/**
 * GamepadDetector 单元测试。
 *
 * 对应 BDD 场景：
 * - Scenario: 启动游戏时已连接标准手柄 -> 应隐藏
 * - Scenario: 仅方向键设备（如遥控器）不算手柄 -> 不隐藏
 * - Scenario: 多设备混合 -> 任一标准手柄即隐藏
 * - Scenario: 空设备列表 -> 不隐藏
 * - Scenario: 虚拟设备（on-screen keyboard）不算手柄 -> 不隐藏
 *
 * 注：android.jar 在 JVM 单元测试中是 stub，InputDevice.SOURCE_* 常量值为 0。
 * 此处显式使用 Android 框架中的真实常量值（见 InputDevice.java 源码），
 * 避免 Robolectric 依赖。
 */
public class GamepadDetectorTest {

    // 来自 android.view.InputDevice 源码的真实常量值
    private static final int SOURCE_KEYBOARD          = 0x00000001;
    private static final int SOURCE_DPAD              = 0x00000002;
    private static final int SOURCE_GAMEPAD           = 0x00000401;
    private static final int SOURCE_TOUCHSCREEN       = 0x00001002;
    private static final int SOURCE_JOYSTICK          = 0x01000010;
    private static final int SOURCE_CLASS_JOYSTICK    = 0x00000010;

    private InputDevice mockDevice(int sources, boolean isVirtual) {
        InputDevice dev = mock(InputDevice.class);
        when(dev.getSources()).thenReturn(sources);
        when(dev.isVirtual()).thenReturn(isVirtual);
        return dev;
    }

    // === Scenario: 启动游戏时已连接标准手柄 ===
    @Test
    public void givenStandardGamepad_whenDetect_thenShouldHide() {
        InputDevice gamepad = mockDevice(SOURCE_GAMEPAD | SOURCE_JOYSTICK, false);
        List<InputDevice> devices = Collections.singletonList(gamepad);

        assertTrue(GamepadDetector.shouldHideControls(devices));
    }

    // === Scenario: 仅 DPAD 设备（遥控器）不算手柄 ===
    @Test
    public void givenDpadOnlyRemote_whenDetect_thenShouldNotHide() {
        InputDevice remote = mockDevice(SOURCE_DPAD, false);
        List<InputDevice> devices = Collections.singletonList(remote);

        assertFalse(GamepadDetector.shouldHideControls(devices));
    }

    // === Scenario: 多设备混合，其中一个是标准手柄 ===
    @Test
    public void givenMixedDevicesWithGamepad_whenDetect_thenShouldHide() {
        InputDevice touch = mockDevice(SOURCE_TOUCHSCREEN, false);
        InputDevice remote = mockDevice(SOURCE_DPAD, false);
        InputDevice gamepad = mockDevice(SOURCE_GAMEPAD | SOURCE_JOYSTICK, false);
        List<InputDevice> devices = Arrays.asList(touch, remote, gamepad);

        assertTrue(GamepadDetector.shouldHideControls(devices));
    }

    // === Scenario: 多设备混合，无标准手柄 ===
    @Test
    public void givenMixedDevicesWithoutGamepad_whenDetect_thenShouldNotHide() {
        InputDevice touch = mockDevice(SOURCE_TOUCHSCREEN, false);
        InputDevice remote = mockDevice(SOURCE_DPAD, false);
        List<InputDevice> devices = Arrays.asList(touch, remote);

        assertFalse(GamepadDetector.shouldHideControls(devices));
    }

    // === Scenario: 空设备列表 ===
    @Test
    public void givenEmptyDevices_whenDetect_thenShouldNotHide() {
        assertFalse(GamepadDetector.shouldHideControls(Collections.emptyList()));
    }

    // === Scenario: null 设备列表 ===
    @Test
    public void givenNullDevices_whenDetect_thenShouldNotHide() {
        assertFalse(GamepadDetector.shouldHideControls(null));
    }

    // === Scenario: 虚拟设备（如屏幕内嵌键盘）不算手柄 ===
    @Test
    public void givenVirtualGamepad_whenDetect_thenShouldNotHide() {
        InputDevice virtual = mockDevice(SOURCE_GAMEPAD | SOURCE_JOYSTICK, true);
        List<InputDevice> devices = Collections.singletonList(virtual);

        assertFalse(GamepadDetector.shouldHideControls(devices));
    }

    // === Scenario: 列表中包含 null 元素 ===
    @Test
    public void givenListWithNullElement_whenDetect_thenShouldNotCrash() {
        InputDevice gamepad = mockDevice(SOURCE_GAMEPAD | SOURCE_JOYSTICK, false);
        List<InputDevice> devices = Arrays.asList(null, gamepad);

        assertTrue(GamepadDetector.shouldHideControls(devices));
    }

    // === Scenario: 游戏中接入手柄（仅 joystick class） ===
    @Test
    public void givenJoystickClassOnly_whenDetect_thenShouldHide() {
        InputDevice joystick = mockDevice(SOURCE_JOYSTICK, false);
        List<InputDevice> devices = Collections.singletonList(joystick);

        assertTrue(GamepadDetector.shouldHideControls(devices));
    }

    // === Scenario: 仅键盘设备不算手柄 ===
    @Test
    public void givenKeyboardOnly_whenDetect_thenShouldNotHide() {
        InputDevice keyboard = mockDevice(SOURCE_KEYBOARD, false);
        List<InputDevice> devices = Collections.singletonList(keyboard);

        assertFalse(GamepadDetector.shouldHideControls(devices));
    }
}
