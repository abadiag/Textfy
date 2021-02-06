using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace TextfyLibTest
{
    [TestClass]
    public class UnitTest1
    {
        private const string template_test_font = @"F:\Repository\Textfy\Assets\Fonts\Test\Test.bmp";
        private const string template_test2_font = @"F:\Repository\Textfy\Assets\Fonts\Test\Test2.bmp";
        private const int ExpectedWidth = 3203;
        private const int ExpectedHeight = 826;

        [TestInitialize]
        public void SetupTests() 
        {
            TextfyConsumer.Api.BitmapApi.open_bmp(template_test_font);
        }

        [TestMethod]
        public void WidthTest()
        {   
            var result = TextfyConsumer.Api.BitmapApi.get_bmp_width();
            Assert.AreEqual(ExpectedWidth, result);
        }

        [TestMethod]
        public void HeightTest()
        {
            TextfyConsumer.Api.BitmapApi.open_bmp(template_test_font);
            var result = TextfyConsumer.Api.BitmapApi.get_bmp_height();
            Assert.AreEqual(ExpectedHeight, result);
        }

        [TestMethod]
        public void CoincidenceTest()
        {
            var result = TextfyConsumer.Api.BitmapApi.get_coincidence(template_test_font, template_test_font, 1);
            Assert.AreEqual(100, result);
        }

        [TestMethod]
        public void NotCoincidenceTest()
        {
            var result = TextfyConsumer.Api.BitmapApi.get_coincidence(template_test2_font, template_test_font, 1);
            Assert.AreEqual(100, result);
        }
    }
}
