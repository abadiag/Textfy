using System;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using Microsoft.Win32;

namespace TextfyConsumer
{
    /// <summary>
    /// Only quick visual tests pourposes MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private string file_1 = String.Empty;
        private string file_2 = String.Empty;
        private string file_to_analize = String.Empty;

        public MainWindow()
        {
            InitializeComponent();
            Init();
        }

        #region Api functionality
        private void Init()
        {
            Task.Run(() => CreateTemplates());
            ThresholdBar.Value = 0.0;
            SetSafeBarValueText();
        }

        private void CreateTemplates()
        {
            Api.BitmapApi.create_templates();
        }

        private string ProcessDocument(string path_to_analize, int th)
        {
            return Task.Run(() => Api.BitmapApi.process_document(path_to_analize, th)).Result;
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
        #endregion

        #region Buttons actions Stuff
        private void DifferenceGetBtn(object sender, MouseButtonEventArgs e)
        {
            int result = GetDifference(file_1, file_2, (int)ThresholdBar.Value);
            ResultTextBox.Text = (result + "%");
        }

        private void Image1LoadBtn(object sender, RoutedEventArgs e)
        {
            string file_img1 = GetFile(".bmp");
            SetSafeImageView(ImgBitmapView, new BitmapImage(new Uri(file_img1)));
        }

        private void Image2LoadBtn(object sender, RoutedEventArgs e)
        {
            string file_img2 = GetFile(".bmp");
            SetSafeImageView(ImgBitmapView2, new BitmapImage(new Uri(file_img2)));
        }

        private void ThresholdBar_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            SetSafeBarValueText();
            e.Handled = true;
        }

        private void AnalizeDocBtn(object sender, RoutedEventArgs e)
        {
            string _txt_result = "No result";
            string _file = GetFile(".bmp");
            _txt_result = string.IsNullOrEmpty(_file) ? _txt_result : ProcessDocument(_file, GetThresholdSafeValue());
            SetSafeTextResult(TextResult_block, _txt_result);
        } 
        #endregion

        #region Safe Thread access controls
        private void SetSafeImageView(System.Windows.Controls.Image control, BitmapImage bmp)
        {
            control.Dispatcher.Invoke(new Action(() =>
            {
                control.Source = bmp;
            }));
        }

        private void SetSafeTextResult(System.Windows.Controls.RichTextBox t_block, string text)
        {
            t_block.Dispatcher.Invoke(new Action(() =>
            {
                t_block.Document.Blocks.Clear();
                t_block.Document.Blocks.Add(new System.Windows.Documents.Paragraph(new System.Windows.Documents.Run(text)));
            }));
        }

        private void SetSafeBarValueText()
        {
            barValue.Dispatcher.Invoke(new Action(() => { barValue.Text = ThresholdBar.Value.ToString(); }));
        }

        private int GetThresholdSafeValue()
        {
            int value_ = 0;
            ThresholdBar.Dispatcher.
                Invoke(new Action(() =>
               {
                   _ = int.TryParse(ThresholdBar.Value.ToString(), out value_);
               }));
            return value_;
        }
        #endregion

        #region Files manip
        private string GetFile(string filter)
        {
            string f_ = String.Empty;
            OpenFileDialog fd = new OpenFileDialog();
            if (fd.ShowDialog().HasValue)
            {
                if (fd.FileName.Contains(filter))
                {
                    f_ = fd.FileName;
                }
                else
                {
                    MessageBox.Show("File not valid " + file_to_analize);
                }
            }
            return f_;
        } 
        #endregion
    }
}