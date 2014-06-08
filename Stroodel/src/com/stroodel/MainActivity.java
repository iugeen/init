package com.stroodel;

import java.io.DataOutputStream;
import java.io.File;
import java.io.IOException;

import com.calibrate.CalibrateActivity;
import com.properties.PropertiesActivity;

import android.os.Bundle;
import android.os.Environment;
import android.app.Activity;
import android.content.Intent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener
{
	
	public Button btnCalibrate, btnProperties;
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
	    
//	    TextView tv = (TextView)findViewById(R.id.textViewMain);
//        tv.setText(stringFromJNI());

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
	}

	@Override
	public void onClick(View v) 
	{
		// TODO Auto-generated method stub
	      switch(v.getId()) 
	      {
	        case R.id.btnCalibrate:
			        act = new Intent(v.getContext(),CalibrateActivity.class);
			        act.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
			        startActivity(act);
	          break;
	        case R.id.btnProperties:
			        act = new Intent(v.getContext(),PropertiesActivity.class);
			        act.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
			        startActivity(act);
	          break;
	      }
	}

}
