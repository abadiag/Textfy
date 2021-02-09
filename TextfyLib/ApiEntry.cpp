#include "pch.h"
#include "ApiEntry.h"


// DLL internal state variables:
TEXTFYLIB_API bitmap_image* bmp;  // Previous value, if any
TEXTFYLIB_API templates_factory* templ_factory;

TEXTFYLIB_API void open_bmp(const char* file_name)
{
	std::cout << "file name " << file_name << std::endl;
	bmp = new bitmap_image(file_name);
}

TEXTFYLIB_API void resize_bmp(const char* file_in, const char* file_out)
{
	std::cout << "file name " << file_in << std::endl;
	bitmap_image img(file_in);
	bitmap_image img_resized(800, 600);
	resize(img, 800, 600, &img_resized);
	img_resized.save_image(file_out);
}

TEXTFYLIB_API void save_bmp(const char* file_name)
{
	bmp->save_image(file_name);
}

TEXTFYLIB_API void flip_bmp(const char* V_H)
{
	if (V_H == "V")
	{
		bmp->vertical_flip();
	}
	else {
		bmp->horizontal_flip();
	}
}

TEXTFYLIB_API bitmap_image::rgb_t get_pixel_bmp(int x, int y)
{
	return  bmp->get_pixel(x, y);
}

TEXTFYLIB_API void set_pixel_bmp(int x, int y, bitmap_image::rgb_t rgb)
{
	bmp->set_pixel(x, y, rgb);
}

TEXTFYLIB_API int get_bmp_width()
{
	return  bmp->width();
}

TEXTFYLIB_API int get_bmp_height()
{
	return  bmp->height();
}

TEXTFYLIB_API bitmap_image get_bmp(const char* file_name)
{
	return  bitmap_image(file_name);
}

TEXTFYLIB_API void get_bmp_stream(unsigned char** pMemoryBuffer, int* size)
{
	std::ofstream o_str("F:\\Repository\\Textfy\\Assets\\Fonts\\Results\\prova.bmp", ios::binary);

	bmp->get_image_stream(o_str);
	*size = 1;

}

TEXTFYLIB_API void rotate_bmp(float angle)
{}

TEXTFYLIB_API void get_bmp_stream(unsigned char* pMemoryBuffer, int* pSize)
{
	std::vector<unsigned char> d;
	d.push_back(0xfe);
	*pSize = bmp->get_data_size();
}

TEXTFYLIB_API int get_bmp_data(unsigned char** pArray, int* pSize)
{
	*pSize = bmp->get_data_size();
	*pArray = bmp->get_data().data();
	return 1;
}

TEXTFYLIB_API MYSTRSTRUCT TestStringInStruct()
{
	//// Assuming that the buffer is big enough.
	//StringCbCatW(pStruct->buffer, pStruct->size, (STRSAFE_LPWSTR)L"++");
	//std::cout << "message from c# "<<pStruct->buffer << std::endl;
	//std::cout << "size of the message " << pStruct->size << std::endl;
	MYSTRSTRUCT s;
	s.buffer = bmp->get_data().data();
	s.size = bmp->get_data_size();
	return s;
}

TEXTFYLIB_API int TestArrayOfStrings(char* ppStrArray[], int count)
{
	int result = 0;
	STRSAFE_LPSTR temp;
	size_t len;
	const size_t alloc_size = sizeof(char) * 10;

	for (int i = 0; i < count; i++)
	{
		len = 0;
		StringCchLengthA(ppStrArray[i], STRSAFE_MAX_CCH, &len);
		result += len;

		temp = (STRSAFE_LPSTR)CoTaskMemAlloc(alloc_size);
		StringCchCopyA(temp, alloc_size, (STRSAFE_LPCSTR)"123456789");

		// CoTaskMemFree must be used instead of delete to free memory.

		CoTaskMemFree(ppStrArray[i]);
		ppStrArray[i] = (char*)temp;
	}

	return result;
}

TEXTFYLIB_API void SayHello()
{
	std::cout << "HELLO!" << std::endl;
}

TEXTFYLIB_API SAFEARRAY* get_bmp_array()
{
	std::vector<ULONG> vecBytes;
	std::ofstream ostr;

	vecBytes.push_back(ostr.flush().hexfloat);

	SAFEARRAY* pSafeArrayOfBytes{}; //bmp->get_image_stream();

	pSafeArrayOfBytes->cbElements = *vecBytes.data();// {};

	//std::fill_n(dta.begin(), dta.size(), t);
	//int size = dta.size();
	//for (int i = 0; i < size; i++)
	//{
	//	vecBytes.push_back((unsigned char)i);
	//}
	//CreateSafeArray<byte, VT_UI1>((unsigned char*)(&(dta)[0]), dta.size(), pSafeArrayOfBytes);

	return pSafeArrayOfBytes;
}

TEXTFYLIB_API int get_coincidence(const char* file_name_a, const char* file_name_b, int threshold)
{
	int result = -1;
	bitmap_image image1(file_name_a);
	bitmap_image image2(file_name_b);
	cout << "Comparing file a: " << file_name_a << " and file b: " << file_name_b << endl;
	Letter a(image1);
	Letter b(image2);
	a.contrast_image();
	b.contrast_image();

	a.crop_to_letter_size();
	b.crop_to_letter_size();

	result = a.percentCoincidence(b, threshold);
	cout << "percentage: " << result << "with threshold " << threshold << endl;
	return result;
}

TEXTFYLIB_API void create_templates()
{
	bitmap_image faunces_bmp("F:\\Repository\\Textfy\\Assets\\Fonts\\Faunces\\Fraunces.bmp");
	document faunces(faunces_bmp);

	bitmap_image inconsolata_bmp("F:\\Repository\\Textfy\\Assets\\Fonts\\Inconsolata\\inconsolata.bmp");
	document inconsolata(inconsolata_bmp);

	bitmap_image ptserif_bmp("F:\\Repository\\Textfy\\Assets\\Fonts\\PTSerif\\PTSerif.bmp");
	document ptserif(ptserif_bmp);

	bitmap_image roboto_bmp("F:\\Repository\\Textfy\\Assets\\Fonts\\Roboto\\Roboto.bmp");
	document roboto(roboto_bmp);

	bitmap_image ubuntu_bmp("F:\\Repository\\Textfy\\Assets\\Fonts\\Ubuntu\\Ubuntu.bmp");
	document ubuntu(ubuntu_bmp);

	std::vector<document> docs;
	docs.push_back(faunces);
	docs.push_back(inconsolata);
	docs.push_back(ptserif);
	docs.push_back(roboto);
	docs.push_back(ubuntu);

	std::vector <const char*> docs_path;
	docs_path.push_back("F:\\Repository\\Textfy\\Assets\\Fonts\\Faunces\\Fraunces.txt");
	docs_path.push_back("F:\\Repository\\Textfy\\Assets\\Fonts\\Inconsolata\\Inconsolata.txt");
	docs_path.push_back("F:\\Repository\\Textfy\\Assets\\Fonts\\PTSerif\\PTSerif.txt");
	docs_path.push_back("F:\\Repository\\Textfy\\Assets\\Fonts\\Roboto\\Roboto.txt");
	docs_path.push_back("F:\\Repository\\Textfy\\Assets\\Fonts\\Ubuntu\\Ubuntu.txt");

	templ_factory = new templates_factory(docs, docs_path);
	templ_factory->process_documents();
	cout << "Templates loaded" << endl;
}

TEXTFYLIB_API char* process_document(const char* file_name, int threshold)
{
	string text_result = "NO_RESULT";
	cout << "Opening file: " << file_name << endl;
	bitmap_image doc_img(file_name);
	document doc(doc_img);
	doc.scan_document();
	doc.set_text(templ_factory->get_templates(), threshold);
	text_result = doc.get_text();
	cout << "result from library " << "\n" << text_result << endl;
	//doc.export_document("F:\\Repository\\Textfy\\Assets\\Results\\Faunces\\");
	return strcpy(new char[text_result.size()], text_result.c_str());

}


