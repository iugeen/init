package com.calibrate;

import com.stroodel.MainActivity;
import com.stroodel.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;


public class CalibrateActivity extends Activity implements OnClickListener
{
	  private CameraPreview cp = null;
	  private Intent act;
	  private Button btnCalib;
	
	  @Override
	  protected void onCreate(Bundle savedInstanceState) 
	  {
	    super.onCreate(savedInstanceState);
	    setContentView(R.layout.calibrate_activity);
	    btnCalib =(Button)findViewById(R.id.btnCalib);
	    btnCalib.setOnClickListener(this);
	    
	    cp = (CameraPreview) findViewById(R.id.cp);
	    cp.getAlpha();
	   }

	@Override
	public void onClick(View v) 
	{
		// TODO Auto-generated method stub
	      switch(v.getId()) 
	      {
	        case R.id.btnCalib:
	        	    cp = null;
			        act = new Intent(v.getContext(),MainActivity.class);
			        act.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
			        startActivity(act);
	          break;
	      }
	}
	  	  
}
