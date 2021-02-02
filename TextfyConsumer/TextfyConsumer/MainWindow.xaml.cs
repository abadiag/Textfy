﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;
using System.IO;
using Microsoft.Win32;

namespace TextfyConsumer
{
    /// <summary>
    /// Lógica de interacción para MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static string path = @"F:\Repository\Textfy\Assets\image_check_bmp.bmp";
        private static string a_1 = @"F:\Repository\Textfy\Assets\A.bmp";
        private static string a_2 = @"F:\Repository\Textfy\Assets\A2.bmp";
        private static string d_1 = @"F:\Repository\Textfy\Assets\D2.bmp";
        private static string output_path = @"F:\Repository\Textfy\Assets\image_output_bmp.bmp";

        private static string text_image = @"F:\Repository\Textfy\Assets\text_image.bmp";
        private static string template_test_font = @"F:\Repository\Textfy\Assets\Fonts\Test\Test.bmp";

        private string file_1 = String.Empty;
        private string file_2 = String.Empty;

        public MainWindow()
        {
            InitializeComponent();
            DoProcesses();
        }

        private async void DoProcesses()
        {
            try
            {
                await Task.Run(() => CreateTemplates());
                unsafe
                {     
                    ProcessDocument();
                }
            }catch(Exception e) 
            {
                Console.WriteLine(e.Message);
            }
        }

        private void CreateTemplates()
        {
           
                Api.BitmapApi.create_templates();
            
        }


        private void ProcessDocument() 
        {
           var text_result =  Api.BitmapApi.process_document(text_image); 
           Console.WriteLine("result is : " + text_result);
        }

        private int GetDifference(string img1, string img2, int th) 
        {
            return Api.BitmapApi.get_coincidence(img1, img2, th);
        }

        private void GetStream() 
        {

            Api.BitmapApi.get_bmp_stream(out var b, out var result);
            Console.WriteLine(result);
        }

        private void Button_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            int result = GetDifference(file_1, file_2, (int)ThresholdBar.Value);
            ResultTextBox.Text = result + "%";
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog fd = new OpenFileDialog();
            if (fd.ShowDialog().HasValue) 
            {
                 file_1 = fd.FileName;
                if (file_1.Contains(".bmp")) 
                {
                    ImgBitmapView.Source = new BitmapImage(new Uri(file_1));
                }
            
            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            OpenFileDialog fd = new OpenFileDialog();
            if (fd.ShowDialog().HasValue)
            {
                file_2 = fd.FileName;
                if (file_2.Contains(".bmp"))
                {
                    ImgBitmapView2.Source = new BitmapImage(new Uri(file_2));
                }
            }
        }
    }
}