package com.stroodel;

import java.io.DataOutputStream;
import java.io.File;
import java.io.IOException;

import com.calibrate.CalibrateActivity;
import com.detect.DetectActivity;
import com.properties.PropertiesActivity;
import com.space.SpaceActivity;

import android.os.Bundle;
import android.os.Environment;
import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener
{
	
	public Button btnCalibrate, btnProperties, btnDetect, btnSpatial;
	final  String folderName = "/dizertatie";
	public Intent act;

	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);

	    btnCalibrate = (Button)findViewById(R.id.btnCalibrate);
	    btnCalibrate.setOnClickListener(this);
	    btnProperties = (Button)findViewById(R.id.btnProperties);
	    btnProperties.setOnClickListener(this);
	    btnDetect = (Button)findViewById(R.id.btnDetection);
	    btnDetect.setOnClickListener(this);
	    btnSpatial = (Button)findViewById(R.id.btnSpatial);
	    btnSpatial.setOnClickListener(this);
	    
	    testFolder();
	    try {
			setUvcParameter();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	
	public void testFolder()
	{
		File folder = new File(Environment.getExternalStorageDirectory() + folderName);
		boolean success = true;
		if (!folder.exists()) {
		    success = folder.mkdir();
		}
		if (success) 
		{
		    // test if files exist
		} 
		else 
		{
		    // asta este .... 
		}
	}
	
	public void setUvcParameter() throws IOException, InterruptedException
	{
		Process process = null;
		process = Runtime.getRuntime().exec("su");
		DataOutputStream out = new DataOutputStream(process.getOutputStream());
		out.writeBytes("echo 128 > /sys/module/uvcvideo/parameters/quirks\n");
		out.writeBytes("exit\n");  
		out.flush();
		process.waitFor();
		
		Process process1 = null;
		process1 = Runtime.getRuntime().exec("su");
		DataOutputStream out1 = new DataOutputStream(process.getOutputStream());
		out1.writeBytes("chmod 666 /dev/video*\n");
		out1.writeBytes("exit\n");  
		out1.flush();
		process1.waitFor();
	}

	@Override
	public void onClick(View v) 
	{
		// TODO Auto-generated method stub
	      switch(v.getId()) 
	      {
	        case R.id.btnCalibrate:
				act = new Intent(v.getContext(),CalibrateActivity.class);
				startActivity(act);
	            break;
	        case R.id.btnProperties:
		        act = new Intent(v.getContext(),PropertiesActivity.class);
		        startActivity(act);
		        break;
	        case R.id.btnDetection:
		        act = new Intent(v.getContext(),DetectActivity.class);
		        startActivity(act);
		        break;
	        case R.id.btnSpatial:
		        act = new Intent(v.getContext(),SpaceActivity.class);
		        startActivity(act);
	            break;
	      }
	}
}
