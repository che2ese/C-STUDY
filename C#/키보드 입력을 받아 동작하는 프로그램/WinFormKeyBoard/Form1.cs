using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormKeyBoard
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.A )
            {
                MessageBox.Show("A 키가 눌렸습니다.");
            }
            if (e.KeyCode == Keys.D1)
            {
                MessageBox.Show("1번 키가 눌렸습니다.");
            }
            if (e.Control.Equals(true))
            {
                MessageBox.Show("컨트롤 키가 눌렸습니다.");
            }
            
            switch (e.KeyCode) 
            { 
                case Keys.D2:
                    MessageBox.Show("2번 키가 눌렸습니다.");
                    break;
                case Keys.D3:
                    MessageBox.Show("3번 키가 눌렸습니다.");
                    break;
                case Keys.D4:
                    MessageBox.Show("4번 키가 눌렸습니다.");
                    break;
                case Keys.D5:
                    MessageBox.Show("5번 키가 눌렸습니다.");
                    break;
            }
        }
        
        // 나머지 키들
        private void Form1_KeyUp(object sender, KeyEventArgs e)
        {
            MessageBox.Show(e.KeyCode.ToString());
        }
    }
}
