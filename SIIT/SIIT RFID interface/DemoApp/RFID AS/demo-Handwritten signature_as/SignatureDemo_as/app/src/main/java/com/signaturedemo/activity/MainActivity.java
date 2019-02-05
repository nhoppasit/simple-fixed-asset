package com.signaturedemo.activity;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.net.Uri;
import android.graphics.Canvas;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import com.signaturedemo.R;
import com.signaturedemo.view.SignatureView;

import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

/**
 * 个性签名demo
 * @author WuShengjun
 * @date 2016年9月13日
 */
public class MainActivity extends Activity implements View.OnClickListener {

	private SignatureView view_signature; //绘图画板
	private Button btn_clear, btn_save, btn_scan; //清除、保存、浏览按钮
	
	private String mPath = Environment.getExternalStorageDirectory() + File.separator
			+ "Signature" + File.separator;  //图片保存的路径
	private String bmpName; //图片名称
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		init();
		
		bmpName = getString(R.string.text_signature) + System.currentTimeMillis() + ".png";
	}
	
	@Override
	protected void onSaveInstanceState(Bundle outState) {
		// TODO Auto-generated method stub
		super.onSaveInstanceState(outState);
	}
	
	@Override
	protected void onRestoreInstanceState(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onRestoreInstanceState(savedInstanceState);
	}
	
	private void init() {
		view_signature = (SignatureView) findViewById(R.id.view_signature);
		btn_clear = (Button) findViewById(R.id.btn_clear);
		btn_save = (Button) findViewById(R.id.btn_save);
		btn_scan = (Button) findViewById(R.id.btn_scan);
		
		btn_clear.setOnClickListener(this);
		btn_save.setOnClickListener(this);
		btn_scan.setOnClickListener(this);
	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch (v.getId()) {
		case R.id.btn_clear: //清除
			view_signature.clear();
			break;
		case R.id.btn_save: //保存图片
			saveBitmap(mPath + bmpName);
			break;
		case R.id.btn_scan: //浏览图片
			scanPicture();
			break;

		default:
			break;
		}
	}
	
	private void saveBitmap(String path) {
		
//		view_signature.setDrawingCacheEnabled(true);
//		view_signature.measure(MeasureSpec.makeMeasureSpec(0, MeasureSpec.UNSPECIFIED),
//				MeasureSpec.makeMeasureSpec(0, MeasureSpec.UNSPECIFIED));
//		view_signature.layout(0, 0, view_signature.getMeasuredWidth(), view_signature.getMeasuredHeight());
//		view_signature.buildDrawingCache();
//		
//		Bitmap bmp = view_signature.getDrawingCache(); 
		
		
		Bitmap bmp = Bitmap.createBitmap(view_signature.getMeasuredWidth(), view_signature.getMeasuredHeight(), Config.ARGB_8888);
		view_signature.draw(new Canvas(bmp));
		
		creatBitmapFile(bmp, path);
	}

	/**
	 * 保存签名文件图片
	 * @param bmp Bitmap图片对象
	 * @param path 保存的路径
	 */
	public void creatBitmapFile(Bitmap bmp, String path) {
		try {
			File file = new File(mPath); 
			if(!file.exists()) { //判断文件夹是否存在，不存在则创建
				file.mkdir();
			}
			
			file = new File(path);
			if(!file.exists()) {
				file.createNewFile();
			}
			
			FileOutputStream fileOut = new FileOutputStream(file);
			bmp.compress(Bitmap.CompressFormat.PNG, 100, fileOut);
			
			fileOut.flush();
			fileOut.close();
			
			updatePhotos(file); //更新图库
			Toast.makeText(this, R.string.msg_save_succ, Toast.LENGTH_SHORT).show();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.e("creatBitmapFile", e.getMessage());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			Log.e("creatBitmapFile", e.getMessage());
			e.printStackTrace();
		} finally {
		}

	}
	
	/**
	 * 打开图库
	 */
	private void scanPicture() {
//		File file = new File(mPath);
//		if(file == null || !file.exists()) {
//			Toast.makeText(this, "还没保存有图片哦~", Toast.LENGTH_SHORT).show();
//			return;
//		}
		
//		Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
//		intent.addCategory(Intent.CATEGORY_DEFAULT);
//		intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
//		intent.setDataAndType(Uri.fromFile(file), "file/*");
//		startActivity(intent);

    	Intent it_gallery = new Intent();
		it_gallery.addCategory(Intent.CATEGORY_OPENABLE);
		it_gallery.setType("image/*");
		startActivity(it_gallery);
	}
	
	 /**
     * 发送广播，图库更新照片
     * @param file 新增的图片
     */
    private void updatePhotos(File file) {
    	Intent intent = new Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE);
        Uri uri = Uri.fromFile(file);
        intent.setData(uri);
        sendBroadcast(intent);
    }
}
