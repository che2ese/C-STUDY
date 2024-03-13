using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FileCopySearch
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label3_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbd  = new FolderBrowserDialog();
            if(fbd.ShowDialog() == DialogResult.OK)
            {
                label3.Text = fbd.SelectedPath;
                label8.Text = "검색 경로가 설정되었습니다.";
            }
        }

        private void label4_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if(ofd.ShowDialog() == DialogResult.OK)
            {
                label4.Text = ofd.FileName;
                label8.Text = "복사할 파일이 선택되었습니다.";
            }
        }

        private void label5_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            if (fbd.ShowDialog() == DialogResult.OK)
            {
                label5.Text = fbd.SelectedPath;
                label8.Text = "파일을 복사할 위치가 선택되었습니다.";
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string[] files = Directory.GetFiles(label4.Text, $"*.txt", SearchOption.AllDirectories);
            foreach(string a in files)  
            {
                try
                {
                    FileInfo file1 = new FileInfo(a);
                    if (file1.Length > 10000 && file1.Name.Length < 15 && file1.DirectoryName.Replace(label4.Text + "\\","").Length < 30)
                    {
                        string pathtemp = file1.DirectoryName.Replace(label4.Text + "\\", "");

                        string filename = "파일명:" + String.Format("{0,15}",file1.Name);
                        string filepath = "/ 파일 경로:" + String.Format("{0,30}", pathtemp);
                        string filesize = " / 파일 크기:" + file1.Length + " byte";
                        listBox1.Items.Add(filename + filepath + filesize);
                    }
                }
                catch { }
            }
            label8.Text = "파일 검색이 완료되었습니다.";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string[] source = label4.Text.Split('\\');
            string name = source[source.Length - 1];
            File.Copy(label4.Text, label5.Text + "\\" + name);
            label8.Text = "파일 복사가 완료되었습니다.";
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }
    }
}
