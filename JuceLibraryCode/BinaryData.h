/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   shimlaIcon_png;
    const int            shimlaIcon_pngSize = 35653;

    extern const char*   smartAssIcon_png;
    const int            smartAssIcon_pngSize = 82279;

    extern const char*   splash1_png;
    const int            splash1_pngSize = 139875;

    extern const char*   splash3_png;
    const int            splash3_pngSize = 62717;

    extern const char*   splash2_png;
    const int            splash2_pngSize = 102915;

    extern const char*   beginScreen_png;
    const int            beginScreen_pngSize = 103402;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
