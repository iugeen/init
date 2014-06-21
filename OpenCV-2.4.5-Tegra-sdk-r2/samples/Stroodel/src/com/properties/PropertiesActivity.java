package com.properties;

import com.stroodel.MainActivity;
import com.stroodel.R;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;


public class PropertiesActivity extends Activity implements OnClickListener
{
	  private Intent act;
	  private Button btnProp;

	  @Override
	  protected void onCreate(Bundle savedInstanceState) 
	  {
	    super.onCreate(savedInstanceState);
	    setContentView(R.layout.properties_activity);
	    //btnProp =(Button)findViewById(R.id.btnProp);
	    //btnProp.setOnClickListener(this);
	   }

	@Override
	public void onClick(View v) 
	{
		// TODO Auto-generated method stub
	      switch(v.getId()) 
	      {
	        case R.id.btnSpatial:
			        act = new Intent(v.getContext(),MainActivity.class);
			        act.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
			        startActivity(act);
	          break;
	      }
	}
}
