package com.pokeemerald.experimental;

import android.graphics.Rect;
import android.hardware.input.InputManager;
import android.os.Bundle;
import android.os.Build;
import android.view.InputDevice;
import android.view.View;
import android.view.ViewGroup;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.libsdl.app.SDLActivity;

public class PokeEmeraldActivity extends SDLActivity {
    private GbaControlsView mControlsView;
    private InputManager mInputManager;
    private final InputManager.InputDeviceListener mDeviceListener =
            new InputManager.InputDeviceListener() {
                @Override
                public void onInputDeviceAdded(int deviceId) {
                    updateControlsVisibility();
                }
                @Override
                public void onInputDeviceRemoved(int deviceId) {
                    updateControlsVisibility();
                }
                @Override
                public void onInputDeviceChanged(int deviceId) {
                    updateControlsVisibility();
                }
            };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mControlsView = new GbaControlsView(this);
        mLayout.addView(mControlsView, new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT));
        mInputManager = (InputManager) getSystemService(INPUT_SERVICE);
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (mInputManager != null) {
            mInputManager.registerInputDeviceListener(mDeviceListener, null);
        }
        // 处理 Activity 恢复时手柄已连接的情况
        updateControlsVisibility();
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (mInputManager != null) {
            mInputManager.unregisterInputDeviceListener(mDeviceListener);
        }
    }

    private void updateControlsVisibility() {
        if (mControlsView == null || mInputManager == null) return;

        List<InputDevice> devices = new ArrayList<>();
        for (int id : mInputManager.getInputDeviceIds()) {
            InputDevice dev = mInputManager.getInputDevice(id);
            devices.add(dev);
        }

        boolean shouldHide = GamepadDetector.shouldHideControls(devices);
        if (shouldHide) {
            // 隐藏前释放所有按下的虚拟按键，避免卡键
            mControlsView.releaseAll();
            mControlsView.animate().alpha(0f).setDuration(200).withEndAction(
                    new Runnable() {
                        @Override
                        public void run() {
                            mControlsView.setVisibility(View.INVISIBLE);
                        }
                    });
        } else {
            mControlsView.setVisibility(View.VISIBLE);
            mControlsView.animate().alpha(1f).setDuration(200);
        }
    }

    @Override
    public void setOrientationBis(int width, int height, boolean resizable, String hint) {
        // The manifest already keeps this activity in sensor landscape mode.
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        if (!hasFocus) {
            return;
        }

        getWindow().getDecorView().setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                | View.SYSTEM_UI_FLAG_FULLSCREEN
                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_LAYOUT_STABLE);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q && mSurface != null) {
            mSurface.post(() -> {
                int width = mSurface.getWidth();
                int height = mSurface.getHeight();
                mSurface.setSystemGestureExclusionRects(Arrays.asList(
                        new Rect(0, height / 2, width / 5, height),
                        new Rect(width * 4 / 5, height / 2, width, height)));
            });
        }
    }

    @Override
    protected String[] getLibraries() {
        return new String[] { "SDL2", "main" };
    }
}
