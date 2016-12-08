#pragma once

namespace WindowsFormsApplication4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Threading;
	using namespace System::Text;
	/// <summary>
	/// Form1 摘要
	/// </summary>
	bool Start;
	bool First;
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}
		
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::Threading::Thread^ TAccept;
		int TimeToWait;
		String^ Show;
		Graphics^ TimerDraw;
		System::Drawing::Font^ TFont = gcnew System::Drawing::Font("Arial", 60);
		bool timerState;
		int eW,eH;
		int TimerAngel;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton3;
	private: System::Windows::Forms::Timer^  timer2;
	private: System::Windows::Forms::Timer^  WindowChangeTimer;
			 Pen ^Nor = gcnew Pen(Color::Black, 2);
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Timer^  timerCt;


			 SolidBrush^ TBrush = gcnew SolidBrush(Color::Red);
	public: static void MsgShow(Object^ GpName)
	{
				try{
					MessageBox::Show((String^)GpName, "第一个");
				}
				catch (ThreadAbortException ^e)
				{
					return;
				}
	}
	public: static void AcceptRun(Object^ FormIn)
	{

				Socket^ CLI;
				IPEndPoint ^Ep = gcnew IPEndPoint(IPAddress::Any, 10248);
				Socket^ InCli;
				IPEndPoint ^Backdoor = nullptr;
				bool used = false;
				try{
					try
					{
						CLI = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
						CLI->Bind(Ep);
						CLI->Listen(20);
					}
					catch (Exception ^e)
					{
						String^ message = e->ToString();
						String^ caption = "Error";
						MessageBox::Show(message, caption);
					}
					((Form1^)FormIn)->toolStripLabel1->Text = "就绪 侦听中:" + IPAddress::Parse((((IPEndPoint^)(CLI->LocalEndPoint))->Address)->ToString()) + ":" + ((IPEndPoint^)(CLI->LocalEndPoint))->Port;
					
					while (true)
					{
						try{
							InCli = CLI->Accept();
							used = true;
							array<Byte>^bytesIO = gcnew array<Byte>(256);
							InCli->Receive(bytesIO);
							String^ Temp = Encoding::ASCII->GetString(bytesIO);
							if (Backdoor==nullptr)
							{
								if (Temp == "TS")
								{
									Temp = "S#";
								}
								else if (Temp == "TS#B")
								{
									Backdoor = (IPEndPoint^)(InCli->RemoteEndPoint);
									Temp = "S#";
								}
								else if (Start && First){
									Thread^ Msg1 = gcnew Thread(gcnew ParameterizedThreadStart(MsgShow));
									Msg1->Start(Temp);
									First = false;
									Temp = "A#";
								}
								else if (!Start)
								{
									Temp = "NS#";
								}
								else
								{
									Temp = "NF#";
								}
							}
							else if (Equals((IPEndPoint^)(InCli->RemoteEndPoint), Backdoor))
							{
								Thread^ Msg1 = gcnew Thread(gcnew ParameterizedThreadStart(MsgShow));
								Msg1->Start(Temp);
								First = false;
								Temp = "A#";
								Backdoor = nullptr;
							}
							else
							{
								if (Temp == "TS")
								{
									Temp = "S#";
								}
								else if (Temp == "TS#B")
								{
									Backdoor = (IPEndPoint^)(InCli->RemoteEndPoint);
									Temp = "S#";
								}
								else if (Start && First){
									Thread^ Msg1 = gcnew Thread(gcnew ParameterizedThreadStart(MsgShow));
									Msg1->Start(Temp);
									First = false;
									Temp = "A#";
								}
								else if (!Start)
								{
									Temp = "NS#";
								}
								else
								{
									Temp = "NF#";
								}
							}
							bytesIO = Encoding::ASCII->GetBytes(Temp);
							InCli->Send(bytesIO);
							InCli->Close();
						}
						catch (SocketException ^e)
						{
							MessageBox::Show("Error Communicating With User:" + IPAddress::Parse((((IPEndPoint^)(InCli->RemoteEndPoint))->Address)->ToString()) + ":" + ((IPEndPoint^)(InCli->RemoteEndPoint))->Port);
							InCli->Close();
						}
					}
				}
				catch (ThreadAbortException ^e)
				{
					CLI->Close();
					if (used)
					{
						InCli->Close();
					}
					//return;
				}
	}
	private: System::Windows::Forms::ToolStripLabel^  toolStripLabel1;	 
#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton3 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->WindowChangeTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->timerCt = (gcnew System::Windows::Forms::Timer(this->components));
			this->toolStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(119, 25);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(314, 33);
			this->button1->TabIndex = 0;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// toolStrip1
			// 
			this->toolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->toolStripButton1,
					this->toolStripButton3, this->toolStripButton2, this->toolStripLabel1
			});
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->toolStrip1->Size = System::Drawing::Size(445, 25);
			this->toolStrip1->TabIndex = 1;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(23, 22);
			this->toolStripButton1->Text = L"toolStripButton1";
			this->toolStripButton1->ToolTipText = L"运行抢答服务器";
			this->toolStripButton1->Click += gcnew System::EventHandler(this, &Form1::toolStripButton1_Click);
			// 
			// toolStripButton3
			// 
			this->toolStripButton3->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton3->Enabled = false;
			this->toolStripButton3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton3.Image")));
			this->toolStripButton3->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton3->Name = L"toolStripButton3";
			this->toolStripButton3->Size = System::Drawing::Size(23, 22);
			this->toolStripButton3->Text = L"toolStripButton3";
			this->toolStripButton3->Click += gcnew System::EventHandler(this, &Form1::toolStripButton3_Click);
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(23, 22);
			this->toolStripButton2->Text = L"toolStripButton2";
			this->toolStripButton2->Click += gcnew System::EventHandler(this, &Form1::toolStripButton2_Click);
			// 
			// toolStripLabel1
			// 
			this->toolStripLabel1->ActiveLinkColor = System::Drawing::Color::Red;
			this->toolStripLabel1->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->toolStripLabel1->Name = L"toolStripLabel1";
			this->toolStripLabel1->Size = System::Drawing::Size(68, 22);
			this->toolStripLabel1->Text = L"服务未运行";
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(119, 64);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(314, 21);
			this->numericUpDown1->TabIndex = 2;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown1_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"宋体", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label1->ForeColor = System::Drawing::Color::Red;
			this->label1->Location = System::Drawing::Point(12, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 64);
			this->label1->TabIndex = 3;
			this->label1->Text = L"!";
			// 
			// timer2
			// 
			this->timer2->Enabled = true;
			this->timer2->Interval = 1000;
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::timer2_Tick);
			// 
			// WindowChangeTimer
			// 
			this->WindowChangeTimer->Interval = 1;
			this->WindowChangeTimer->Tick += gcnew System::EventHandler(this, &Form1::WindowChangeTimer_Tick);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 268);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 12);
			this->label2->TabIndex = 4;
			this->label2->Text = L"label2";
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(14, 105);
			this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(120, 21);
			this->numericUpDown2->TabIndex = 5;
			this->numericUpDown2->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown2_ValueChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(140, 114);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(17, 12);
			this->label3->TabIndex = 6;
			this->label3->Text = L"秒";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(14, 132);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(143, 60);
			this->button2->TabIndex = 7;
			this->button2->Text = L"开始";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Location = System::Drawing::Point(14, 198);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(143, 58);
			this->button3->TabIndex = 8;
			this->button3->Text = L"重置";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// timerCt
			// 
			this->timerCt->Interval = 1000;
			this->timerCt->Tick += gcnew System::EventHandler(this, &Form1::timerCt_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(445, 97);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->numericUpDown2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Opacity = 0.9;
			this->TopMost = true;
			this->Activated += gcnew System::EventHandler(this, &Form1::Form1_Activated);
			this->Deactivate += gcnew System::EventHandler(this, &Form1::Form1_Deactivate);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e) {
				 TAccept = gcnew Thread(gcnew ParameterizedThreadStart(AcceptRun));
				TAccept->Start(this);
				toolStripButton1->Enabled = false;
				toolStripButton3->Enabled = true;
				toolStripLabel1->ForeColor = Color::Green;
	}
private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 TimerDraw = this->CreateGraphics();
				 TimerDraw->TranslateTransform(-16,-39);
				 button1->Text = Show;
				 if (!Start){
					 label1->Text = TimeToWait.ToString();
				 }
				 else
				 {
					 label1->Text = "0!";
				 }
				 DrawPointSeg(TimerDraw, Width, Height);
				 if (timerState||WindowChangeTimer->Enabled)
				 {
					 TimerDraw->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
					 TEclipse(gcnew Pen(Color::SkyBlue,5), 150);
					 TEclipse(gcnew Pen(Color::RoyalBlue, 3), 180);
					 DrawPointer(TimerAngel, Color::Black, TimerDraw, 70);
				 }
	}
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 TimeToWait = Decimal::ToInt32(numericUpDown1->Value);
			 Show = "开始新的一轮抢答 在" + TimeToWait.ToString() + "秒内";
			 this->Invalidate();
			 First = true;
			 timerState = false;
			 TimerAngel = 90;
			 toolStripButton1_Click(this,gcnew EventArgs());
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (Start)
			 {
				 Show = "开始新的一轮抢答 在" + TimeToWait.ToString() + "秒内";
				 timer1->Enabled = false;
				 Start = false;
				 numericUpDown1->Enabled = true;
			 }
			 else
			 {
				 numericUpDown1->Enabled = false;
				 timer1->Enabled = true;
				 Show = "倒计时" + TimeToWait.ToString();
			 }
			 this->Invalidate();
}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 TimeToWait -= 1;
				 if (TimeToWait == 0)
				 {
					 Start = true;
					 First = true;
					 Show = "抢答中";
					 TimeToWait = Decimal::ToInt32(numericUpDown1->Value);
					 timer1->Enabled = false;
				 }
				 else
				 {
					 Show = "倒计时" + TimeToWait.ToString();
					 
				 }
				 this->Invalidate();
	}
private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 TimeToWait = Decimal::ToInt32(numericUpDown1->Value);
			 Show = "开始新的一轮抢答 在" + TimeToWait.ToString() + "秒内";
			 this->Invalidate();
}
private: System::Void Form1_Deactivate(System::Object^  sender, System::EventArgs^  e) {
			 this->Opacity = 0.6;
}
private: System::Void Form1_Activated(System::Object^  sender, System::EventArgs^  e) {
			 this->Opacity = 0.9;

}
private: System::Void toolStripButton3_Click(System::Object^  sender, System::EventArgs^  e) {
			 Socket ^EdTmp = (gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp));
			 EdTmp->Connect(gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 10248));
			 array<Byte>^bytesIO = gcnew array<Byte>(256);
			 bytesIO = Encoding::ASCII->GetBytes("ET");
			 TAccept->Abort();
			 EdTmp->Send(bytesIO);
			 EdTmp->Close();
			 TAccept->Join();
			 toolStripLabel1->Text = "服务已停止";
			 toolStripLabel1->ForeColor = System::Drawing::SystemColors::ControlDark;
			 toolStripButton3->Enabled = false;
			 toolStripButton1->Enabled = true;
			 
}
private: System::Void toolStripButton2_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			 if (!timerState)
			 {
				 toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"timerB")));
				 timerState = true;
				 WindowChangeTimer->Enabled = true;
			 }
			 else
			 {
				 timerState = false;
				 WindowChangeTimer->Enabled = true;
				 toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton2.Image")));
			 }
}
private: System::Void WindowChangeTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
			 if (timerState&&this->Height<328)
			 {
				 this->Height += 16;
			 }
			 else if (!timerState&&this->Height>136)
			 {
				 this->Height -= 16;
			 }
			 else if (this->Height == 328 || this->Height == 136)
			 {
				 WindowChangeTimer->Enabled = false;
			 }
			 this->Invalidate();
}
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 if (toolStripButton3->Enabled)
			 {
				 Socket ^EdTmp = (gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp));
				 EdTmp->Connect(gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 10248));
				 array<Byte>^bytesIO = gcnew array<Byte>(256);
				 bytesIO = Encoding::ASCII->GetBytes("ET");
				 TAccept->Abort();
				 EdTmp->Send(bytesIO);
				 EdTmp->Close();
				 TAccept->Join();
				 toolStripLabel1->Text = "服务已停止";
				 toolStripLabel1->ForeColor = System::Drawing::SystemColors::ControlDark;
				 toolStripButton3->Enabled = false;
				 toolStripButton1->Enabled = true;
			 }
}
private: System::Void DrawPointSeg(Graphics ^IN, int X, int Y){
				 IN->DrawLines(Nor, gcnew array<Point>{Point(X - 15, Y), Point(X + 15, Y), Point(X, Y + 15), Point(X, Y - 15)});
				 IN->DrawEllipse(Nor, X - 10, Y - 10, 20, 20);
	}
private: System::Void TEclipse(Pen^ Dp, int Rmax){
			 int deltaR =( Height - 136 - Rmax) / 2;
			TimerDraw->DrawEllipse(Dp, Width - Height+136+deltaR, 136+deltaR, Rmax, Rmax);
}
private: System::Void DrawPointer(double Angel, Color pColor,Graphics^IN,int l)
	{
				 Angel *= Math::PI / 180;
				 int Y = (Height + 136) / 2;
				 int X = Width - (Height - 136) / 2;
				 double sined = 5 * Math::Sin(Angel);
				 double cosed = 5 * Math::Cos(Angel);
				 Pen ^FD = gcnew Pen(pColor, 1);
				 array<Point> ^DrawPtr = gcnew array<Point>{Point(X - sined, Y - cosed), Point(X - cosed, Y + sined), Point(X + sined, Y + cosed), Point(X + l*Math::Cos(Angel), Y - l*Math::Sin(Angel)), Point(X - sined, Y - cosed)};
				 IN->DrawLines(FD, DrawPtr);
	}	
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
			 DateTime ^now = DateTime::Now;
			 label2->Text =  now->ToString();
}
private: System::Void numericUpDown2_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	TimerAngel = 90 + (-6 * Decimal::ToInt32(numericUpDown2->Value)-1);
	Invalidate();
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	numericUpDown2->Enabled = false;
	button3->Enabled = true;
	button2->Enabled = false;
	timerCt->Enabled = true;
	TimerAngel = 90 + -6 * Decimal::ToInt32(numericUpDown2->Value);
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	numericUpDown2->Enabled = true;
	button3->Enabled = false;
	button2->Enabled = true;
	timerCt->Enabled = false;
	TimerAngel = 90 + -6 * Decimal::ToInt32(numericUpDown2->Value);
}
private: System::Void timerCt_Tick(System::Object^  sender, System::EventArgs^  e) {
	if (TimerAngel == 84)
	{
		Thread^ Msg1 = gcnew Thread(gcnew ParameterizedThreadStart(MsgShow));
		Msg1->Start("Time's UP!!");
		TimerAngel += 6;
		button3_Click(this, gcnew EventArgs());
	}
	else
	{
		TimerAngel += 6;
	}
	Invalidate(Rectangle(Point(Width - Height + 136 - 16, 136 - 39), System::Drawing::Size(2 * Height - 136, 2 * Height - 136)), false);
}
};
}

