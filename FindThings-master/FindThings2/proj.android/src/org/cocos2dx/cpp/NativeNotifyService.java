package org.cocos2dx.cpp;

import android.app.Activity;

import com.tallbigup.android.gds.nativenotify.NotifyManager;

public class NativeNotifyService {
	
	private static Activity activity;
	
	public static void init(Activity activity){
		NativeNotifyService.activity = activity;
	}
	
	public static void startNativeNotify(){
		NotifyManager.setNextNotification(activity, 1000*60*60*12, "������2015", "��Ϣʱ�䵽�ˣ�һ����������ˣ��!");
	}
}
