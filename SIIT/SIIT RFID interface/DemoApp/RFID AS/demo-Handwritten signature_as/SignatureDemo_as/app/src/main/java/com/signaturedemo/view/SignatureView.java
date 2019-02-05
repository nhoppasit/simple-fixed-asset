package com.signaturedemo.view;


import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;

public class SignatureView extends View {

	private Paint mPaint = new Paint();
	private Path mPath = new Path();

	public SignatureView(Context context, AttributeSet attrs, int defStyleAttr) {
		super(context, attrs, defStyleAttr);
		// TODO Auto-generated constructor stub

		init();
	}

	public SignatureView(Context context, AttributeSet attrs) {
		super(context, attrs);
		// TODO Auto-generated constructor stub

		init();
	}

	public SignatureView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub

		init();
	}

	private void init() {
		mPaint.setAntiAlias(true);
		mPaint.setColor(Color.BLACK);
		mPaint.setStyle(Paint.Style.STROKE);
		mPaint.setStrokeJoin(Paint.Join.ROUND);
		mPaint.setStrokeWidth(5f);
	}

	@Override
	protected void onDraw(Canvas canvas) {
		// TODO Auto-generated method stub
		canvas.drawPath(mPath, mPaint);
	}

	private float cur_x, cur_y;
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		// TODO Auto-generated method stub

		float eventX = event.getX();
		float eventY = event.getY();

		switch (event.getAction()) {
		case MotionEvent.ACTION_DOWN:
			cur_x = eventX;
			cur_y = eventY;
			mPath.moveTo(eventX, eventY);
			return true;
		case MotionEvent.ACTION_MOVE:
		case MotionEvent.ACTION_UP:
			myDraw(event); //¼õ¾â³ÝÃè»æ
			mPath.quadTo(cur_x, cur_y, eventX, eventY);
			
//			if(Math.abs(cur_x - eventX) > 2 || Math.abs(cur_y - eventY) > 2) invalidate();
			
			cur_x = eventX;
			cur_y = eventY;
			break;

		default:
			return false;
		}

		invalidate();

		return true;
	}

	/**
	 * »æÍ¼Ê±¼õ¾â³Ý²Ù×÷
	 * @param event
	 */
	private void myDraw(MotionEvent event) {
		int historySize = event.getHistorySize();
		for(int i=0; i<historySize; i++) {
			float historicalX = event.getHistoricalX(i);
			float historicalY = event.getHistoricalY(i);
			mPath.quadTo(cur_x, cur_y, historicalX, historicalY);
		}
	}

	/**
	 * Çå³ýÃè»æ
	 */
	public void clear() {
		mPath.reset();
		invalidate();
	}

}
