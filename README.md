# Textfy
C++ lib image to text reader

Use of the dynamic .DLL lib from c#:

create desired static extern methods with the same name in 'ApiEntry.h' following the next:
(DllPath must be the location of the .DLL)

[Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
public static extern void create_templates();

the method void create_templates() should be called first of all. It creates the internal db of initial values that will be used in the future analisis.


Process text image .bmp to extract the string:

Phase 1:
call process_document(string file_name);

Get the path of the image and load as bitmap (using Partow header lib):
![alt text](https://github.com/abadiag/Textfy/blob/main/Assets/Fonts/Faunces/Fraunces.bmp?raw=true)

Phase 2:
Detect and separate lines, croping the edges:

![alt text](https://github.com/abadiag/Textfy/blob/main/Assets/lines/line0.bmp?raw=true)

Phase 3:
Detect and extract the columns ('leters or symbols') in each line, getting something such as follow:

![alt text](https://github.com/abadiag/Textfy/blob/main/Assets/letters/letter0_0.bmp?raw=true)

Phase 4:
Compare each letter getting percentage of equal pixels with previously loaded and analized template patterns, the best coincidence will be returned, with it's text value updated:

![alt text](https://github.com/abadiag/Textfy/blob/main/Assets/letters/letter0_0.bmp?raw=true) -->> "A"
