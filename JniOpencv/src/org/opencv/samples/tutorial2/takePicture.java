package org.opencv.samples.tutorial2;

import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;

class takePicture implements OnClickListener {

	Handler workerThreadHandler;
	
	Handler handler = new Handler(){
		@Override
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			
			workerThreadHandler = (Handler)msg.obj;
				
		}
	};
	
	public Handler getHandler()
	{
		return this.handler;
	}
	
	/*
	 * Triggers a message sent to the worker thread which saves 
	 * the current image.
	 * 
	 * (non-Javadoc)
	 * @see android.view.View.OnClickListener#onClick(android.view.View)
	 */
	@Override
	public void onClick(View v) {
		
		Log.d("takePicture", "clicked");

		Message msg = workerThreadHandler.obtainMessage();
		msg.arg1 = 2;
		msg.what = 0;
		workerThreadHandler.sendMessage(msg);
		
	}
	
}