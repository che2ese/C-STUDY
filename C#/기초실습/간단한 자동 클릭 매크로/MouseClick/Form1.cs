using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MouseClick
{
    public partial class Form1 : Form
    {
        int Tick = 0;
        // 위도우 USER 구성 요소 ( 창, 메뉴, 윈도우 사용자 인터페이스 ) 등의 구현을 지원
        [DllImport("user32.dll")] 

        // mouse_event(이벤트 종류, x좌표, y좌표, 휠 스크롤, 마우스 타입)
        static extern void mouse_event(uint dwFlags, uint dx , uint dy, uint dwData, int dwExtraInfo);
        // const : 상수
        const uint L_BUTTON_DOWN = 0x0002; // 지정한 값에 따라 이벤트 변경
        const uint L_BUTTON_UP = 0x0004;
        const uint R_BUTTON_DOWN = 0x0008;
        const uint R_BUTTON_UP = 0x0010;
        public Form1()
        {
            InitializeComponent();
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            label3.Text = Cursor.Position.X.ToString();
            label5.Text = Cursor.Position.Y.ToString();
            Tick++;
            if(Tick == 30)
            {
                Cursor.Position = new Point(500, 391);

                mouse_event(R_BUTTON_DOWN, 0, 0, 0, 0);
                mouse_event(R_BUTTON_UP, 0, 0, 0, 0);
            }
            if (Tick == 60)
            {
                Cursor.Position = new Point(800, 391);

                mouse_event(R_BUTTON_DOWN, 0, 0, 0, 0);
                mouse_event(R_BUTTON_UP, 0, 0, 0, 0);
                Tick = 0;
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            timer1.Enabled = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }
    }
}
