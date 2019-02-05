import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JRadioButton;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JComboBox;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import javax.swing.JScrollPane;
import javax.swing.JTextArea;

import Reader.ReaderAPI;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.UnsupportedEncodingException;

import javax.swing.JCheckBox;

import sdk.Utility;


public class test {

	private JFrame frame;
	private JTextField textField;
	private JTextField textField_1;
	private JTextField textField_2;
	private JTextField textField_3;
	private JTextField textField_4;
	private JComboBox comboBox;
	private JTextArea textArea;
	
	private JCheckBox chckbxNewCheckBox;
	private JCheckBox chckbxNewCheckBox_1;	
	private JCheckBox checkBox;
	private JCheckBox checkBox_1;
	
	private javax.swing.ButtonGroup buttonGroup1;
	int ConnectMode = -1;
	
	int hScanner[] = new int[1];

	int Address = 0;
	 
	int Ants[] = new int[4]; 
	boolean isRun = false;
	private MyThread mt = new MyThread();;
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					test window = new test();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public test() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 628, 640);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		buttonGroup1 = new javax.swing.ButtonGroup();	
		
		final JRadioButton rdbtnTcpip = new JRadioButton("TCP/IP");
		rdbtnTcpip.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				textField.setEditable(true);
				textField_1.setEditable(true);
				textField_2.setEditable(true);
				textField_3.setEditable(true);
				textField_4.setEditable(false);
				comboBox.setEnabled(false);
			}
		});
		rdbtnTcpip.setBounds(6, 6, 70, 23);
		frame.getContentPane().add(rdbtnTcpip);
		
		final JRadioButton rdbtnR = new JRadioButton("R232");
		rdbtnR.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				textField.setEditable(false);
				textField_1.setEditable(false);
				textField_2.setEditable(false);
				textField_3.setEditable(false);
				textField_4.setEditable(true);
				comboBox.setEnabled(true);
			}
		});
		rdbtnR.setBounds(78, 6, 70, 23);
		frame.getContentPane().add(rdbtnR);
		
		final JRadioButton rdbtnR_1 = new JRadioButton("R485");
		rdbtnR_1.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				textField.setEditable(false);
				textField_1.setEditable(false);
				textField_2.setEditable(false);
				textField_3.setEditable(false);
				textField_4.setEditable(true);
				comboBox.setEnabled(true);
			}
		});
		rdbtnR_1.setBounds(150, 6, 70, 23);
		frame.getContentPane().add(rdbtnR_1);
		
		buttonGroup1.add(rdbtnTcpip);
		buttonGroup1.add(rdbtnR);
		buttonGroup1.add(rdbtnR_1);
		rdbtnR.setSelected(true);
		
		textField_4 = new JTextField();
		textField_4.setBounds(274, 166, 45, 21);
		frame.getContentPane().add(textField_4);
		textField_4.setColumns(10);
		
		comboBox = new JComboBox();
		comboBox.setBounds(274, 128, 59, 21);
		frame.getContentPane().add(comboBox);
		
		comboBox.removeAllItems();
        int k = 0;
        int i = 0;
        for (i = 0; i < 22; i++){
            k = i+1;
            comboBox.addItem("COM" + k);
        }
        comboBox.setSelectedIndex(0);
        comboBox.setEditable(false);		
        
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(6, 208, 608, 388);
		frame.getContentPane().add(scrollPane);
		textArea = new JTextArea();
		scrollPane.setViewportView(textArea);
        
		JButton button = new JButton("\u8FDE\u63A5");
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {			
				int res = -1;
				int[] nBaudRate = new int[1];
				short[] HandVer = new short[1];
	            short[] SoftVer = new short[1];
	                        	                   
				if(rdbtnTcpip.isSelected())
				{
					ConnectMode = 0;
					res = ReaderAPI.Net_ConnectScanner(hScanner, textField.getText(),Integer.parseInt(textField_1.getText()),textField_2.getText(), Integer.parseInt(textField_3.getText()));					
				}
				else
				if(rdbtnR.isSelected() || rdbtnR_1.isSelected())
				{
					ConnectMode = 1;
					if(rdbtnR_1.isSelected())
						Address = Integer.parseInt(textField_4.getText());
					nBaudRate[0] = 115200;
					res = ReaderAPI.ConnectScanner(hScanner, comboBox.getSelectedItem().toString(), nBaudRate, Address);
				}
				else 
					return;						   
		          
				if(res == ReaderAPI._OK) 							
					res = ConnectMode == 0 ? ReaderAPI.Net_GetReaderVersion(hScanner[0], HandVer, SoftVer) : ReaderAPI.GetReaderVersion(hScanner[0], HandVer, SoftVer, Address);				
					
				byte [] gBasicParam = new byte[32];	
				if(res == ReaderAPI._OK)
				{					
					textArea.append("版本号 ：" + HandVer[0] + SoftVer[0] + "\n");  					
					res = ConnectMode == 0 ? ReaderAPI.Net_ReadBasicParam(hScanner[0], gBasicParam) : ReaderAPI.ReadBasicParam(hScanner[0], gBasicParam, Address) ;
				}
				
				String str = "";
				byte [] gAutoParam = new byte[32];
				if(res == ReaderAPI._OK)
				{					
					str = Utility.bytes2HexString(gBasicParam, 32);
					textArea.append("机器参数 ：" + str + "\n");
					res = ConnectMode == 0 ? ReaderAPI.Net_ReadAutoParam(hScanner[0], gAutoParam):ReaderAPI.ReadAutoParam(hScanner[0], gAutoParam, Address);				               
				}
				
				if(res == ReaderAPI._OK)
				{
					str = Utility.bytes2HexString(gAutoParam, 32);
					textArea.append("自动模式参数 ：" +  str + "\n"); 
					JOptionPane.showMessageDialog(null, "Connect Reader Success!", "Notice", JOptionPane.INFORMATION_MESSAGE);
				}
				else
				{
					ConnectMode = -1;
					JOptionPane.showMessageDialog(null, "Connect Reader Fail!(Version)", "Warning", JOptionPane.ERROR_MESSAGE);
				}
			}
		});
		button.setBounds(240, 6, 93, 23);
		frame.getContentPane().add(button);
		
		JButton button_1 = new JButton("\u65AD\u5F00");
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int res ;
				res = (ConnectMode == 0 ? ReaderAPI.Net_DisconnectScanner() : (ConnectMode == 1 ? ReaderAPI.DisconnectScanner(hScanner[0]) : -1));
				if(res == ReaderAPI._OK) JOptionPane.showMessageDialog(null, "Disconnect Success!", "Notice", JOptionPane.INFORMATION_MESSAGE);
			}
		});
		button_1.setBounds(240, 49, 93, 23);
		frame.getContentPane().add(button_1);
		
		JLabel lblIp = new JLabel("\u8BFB\u5361\u5668IP\u5730\u5740 ");
		lblIp.setBounds(6, 53, 85, 15);
		frame.getContentPane().add(lblIp);
		
		textField = new JTextField();
		textField.setText("192.168.0.100");
		textField.setBounds(99, 50, 121, 21);
		frame.getContentPane().add(textField);
		textField.setColumns(10);
		
		JLabel label = new JLabel("\u8BFB\u5361\u5668\u7AEF\u53E3 ");
		label.setBounds(6, 91, 85, 15);
		frame.getContentPane().add(label);
		
		textField_1 = new JTextField();
		textField_1.setText("1969");
		textField_1.setBounds(99, 88, 66, 21);
		frame.getContentPane().add(textField_1);
		textField_1.setColumns(10);
		
		JLabel lblip = new JLabel("\u672C\u673AIP\u5730\u5740 ");
		lblip.setBounds(6, 133, 70, 15);
		frame.getContentPane().add(lblip);
		
		JLabel label_1 = new JLabel("\u672C\u673A\u7AEF\u53E3");
		label_1.setBounds(6, 172, 54, 15);
		frame.getContentPane().add(label_1);
		
		textField_2 = new JTextField();
		textField_2.setBounds(99, 130, 121, 21);
		frame.getContentPane().add(textField_2);
		textField_2.setColumns(10);
		
		textField_3 = new JTextField();
		textField_3.setBounds(99, 169, 66, 21);
		frame.getContentPane().add(textField_3);
		textField_3.setColumns(10);
		
		JLabel label_2 = new JLabel("\u4E32\u53E3\u53F7");
		label_2.setBounds(226, 131, 54, 15);
		frame.getContentPane().add(label_2);
		
		JLabel label_3 = new JLabel("485\u5730\u5740");
		label_3.setBounds(226, 169, 54, 15);
		frame.getContentPane().add(label_3);
		
		textField.setEditable(false);
		textField_1.setEditable(false);
		textField_2.setEditable(false);
		textField_3.setEditable(false);
		textField_4.setEditable(true);
		comboBox.setEnabled(true);
		
		chckbxNewCheckBox = new JCheckBox("\u5929\u7EBF1");
		chckbxNewCheckBox.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if(chckbxNewCheckBox.isSelected())
					Ants[0] = 1;
				else
					Ants[0] = 0;
			}
		});
		chckbxNewCheckBox.setBounds(372, 6, 59, 23);
		frame.getContentPane().add(chckbxNewCheckBox);
		
		chckbxNewCheckBox_1 = new JCheckBox("\u5929\u7EBF2");
		chckbxNewCheckBox_1.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if(chckbxNewCheckBox_1.isSelected())
					Ants[1] = 1;
				else
					Ants[1] = 0;
			}
		});
		chckbxNewCheckBox_1.setBounds(433, 6, 59, 23);
		frame.getContentPane().add(chckbxNewCheckBox_1);
		
		checkBox = new JCheckBox("\u5929\u7EBF3");
		checkBox.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if(checkBox.isSelected())
					Ants[2] = 1;
				else
					Ants[2] = 0;
			}
		});
		checkBox.setBounds(494, 6, 59, 23);
		frame.getContentPane().add(checkBox);
		
		checkBox_1 = new JCheckBox("\u5929\u7EBF4");
		checkBox_1.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if(checkBox_1.isSelected())
					Ants[3] = 1;
				else
					Ants[3] = 0;
			}
		});
		checkBox_1.setBounds(555, 6, 59, 23);
		frame.getContentPane().add(checkBox_1);

		final JButton button_2 = new JButton("\u5217\u51FA\u6807\u7B7E");
		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(isRun)
				{
					mt.setEnd(true);
					button_2.setText("列出标签");
				}
				else
				{
					mt = new MyThread();
					mt.start();
					button_2.setText("停止列出");
				}					
				isRun = !isRun;
			}
		});
		button_2.setBounds(372, 49, 93, 23);
		frame.getContentPane().add(button_2);
		
		JButton button_3 = new JButton("\u6E05\u7A7A\u8F93\u51FA");
		button_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				textArea.setText("");
			}
		});
		button_3.setBounds(509, 175, 93, 23);
		frame.getContentPane().add(button_3);
	}
	
	class MyThread extends Thread
	{
		private boolean endThread=false;
		public boolean isRun = false;
		
		 @Override
		    public void run()
		    {
			 isRun = true;
			 while(true)
			 {
				 if (endThread)              
		                break;
		            
				for(int i = 0; i < 4; i ++)
				{
					if (endThread)               
		                break;
		            
					if(Ants[i] == 1)
					{
						if (endThread)               
			                break;
			            
						int ant = (int) Math.pow(2, i);		
						int res = -1;
							
						 switch(ConnectMode)
			             {
			              case 0:
			                 res = ReaderAPI.Net_SetAntenna(hScanner[0], ant);
			                        break;
			              case 1:              	
			                 res = ReaderAPI.SetAntenna(hScanner[0], ant, Address);
			                  if(Address != 0)
								try {
									Thread.sleep(50);
								} catch (InterruptedException e1) {
								// TODO 自动生成的 catch 块
								e1.printStackTrace();
								}
			                      break;
			               }
							 
					int ID_len=0,ID_len_temp=0;
					byte[] IDBuffer = new byte[30*256];
					int[] nCounter = new int[2];
					         
					if(res == ReaderAPI._OK)
					switch(ConnectMode)
				    {
				       case 0://缃戝彛
				       res=ReaderAPI.Net_EPC1G2_ReadLabelID(hScanner[0],1,0,0,null,IDBuffer,nCounter);
				              break;
				        case 1://RS232                 	
				         res=ReaderAPI.EPC1G2_ReadLabelID(hScanner[0],1,0,0,null,IDBuffer,nCounter, Address);
				         if(Address != 0)
						try {
							Thread.sleep(50);
							} catch (InterruptedException e1) {
							// TODO 自动生成的 catch 块
							e1.printStackTrace();
							}
				             break;
				    }
					if(res == ReaderAPI._OK)		
					 {
						  for(i=1;i<nCounter[0];i++){						  
	                            if (IDBuffer[ID_len]>32)//判断EPC长度
	                            {
	                                    nCounter[0]=0;
	                                    break;
	                            }
	                            ID_len_temp += IDBuffer[ID_len] * 2 + 1;
	                            
	                            byte[] b_buffer = new byte[IDBuffer[ID_len] * 2];
	                            System.arraycopy(IDBuffer, ID_len + 1, b_buffer, 0, IDBuffer[ID_len] * 2);
	                            String str = Utility.bytes2HexString(b_buffer, IDBuffer[ID_len] * 2);
	                            
	                            textArea.append("EPC数据  ：" + str + "  " + "LEN == " + IDBuffer[ID_len] + "\n");
	    						textArea.setCaretPosition(textArea.getText().length());
	    						str = "";
	                            
	                            ID_len=ID_len_temp;	                            	                          	                                                   	                           								   						
	                        }					 						
					 }								 
					}
				}		 
			 }
			 isRun = false;
		   }
		    public void setEnd(boolean t)
		    {
		    	endThread=t;
		    }
	}
}
