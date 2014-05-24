package org.opencv.samples.tutorial2;

//import org.opencv.samples.tutorial2.R;

import android.app.Activity;
import android.content.SharedPreferences;
import android.graphics.Matrix;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Toast;

public class JniOpencvActivity extends Activity {
	
	private static final String PREFERENCES_MATRIX = "org.opencv.samples.tutorial2.flipmatrix_";

	private static final String MENU_ITEM_FLIPLR = "Flip Horizontal";
	private static final int MENU_ITEM_ID_FLIPLR = 1;
	private static final String MENU_ITEM_FLIPUD = "Flip Vertical";
	private static final int MENU_ITEM_ID_FLIPUD = 2;
	private static final int MENU_GROUP_FLIP = 1; 
	
    static {
        System.loadLibrary("ImageProc");
    }
	
	CameraPreview cp;
	SharedPreferences preferences;
	SharedPreferences.Editor editor;
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.tutorial2_surface_view);
		
		System.out.println(System.getProperty("java.library.path"));
		
		Toast.makeText(getBaseContext(),">> TEST: " + System.getProperty("java.library.path"), Toast.LENGTH_LONG).show();
		
		preferences = this.getPreferences(MODE_PRIVATE);
		editor = preferences.edit();
		
		cp = (CameraPreview)findViewById(R.id.cameraSurfaceView);
		
		//load preferences to matrix
		Matrix tmp_mx = new Matrix();
		tmp_mx.reset();
		float[] mx_array = new float[9];
		tmp_mx.getValues(mx_array);
		for(int i=0;i<mx_array.length;i++)
		{
			mx_array[i] = preferences.getFloat(PREFERENCES_MATRIX + i,mx_array[i]);
		}
		this.cp.mx.setValues(mx_array);
		
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// TODO Auto-generated method stub
		
		menu.add(MENU_GROUP_FLIP,MENU_ITEM_ID_FLIPLR,Menu.NONE,MENU_ITEM_FLIPLR);
		menu.add(MENU_GROUP_FLIP,MENU_ITEM_ID_FLIPUD,Menu.NONE,MENU_ITEM_FLIPUD);
		
		return super.onCreateOptionsMenu(menu);
	}
	
	@SuppressWarnings("null")
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// TODO Auto-generated method stub
		switch(item.getGroupId())
		{
			case MENU_GROUP_FLIP:
				
				switch(item.getItemId())
				{
					case MENU_ITEM_ID_FLIPLR:
						this.cp.mx.postScale(-1.0f,1.0f);
						this.cp.mx.postTranslate(CameraPreview.IMG_WIDTH, 0);
						break;
						
					case MENU_ITEM_ID_FLIPUD:
						this.cp.mx.postScale(1.0f,-1.0f);
						this.cp.mx.postTranslate(0, CameraPreview.IMG_HEIGHT);
						break;
						
					default:
						Log.e(this.getLocalClassName(), "unrecognized menu id group");
						break;
				}
				
				//save matrix to preferences
				float[] mx_array = new float[9];
				this.cp.mx.getValues(mx_array);
				for(int i=0;i<mx_array.length;i++)
				{
					editor.putFloat(PREFERENCES_MATRIX + i, mx_array[i]);
				}
				editor.commit();
				break;
				
			default:
				Log.e(this.getLocalClassName(), "unrecognized menu group");
				break;
		}
			
		
		return super.onOptionsItemSelected(item);
	}
	
}
