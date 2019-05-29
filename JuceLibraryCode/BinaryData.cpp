/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== README.md ==================
static const unsigned char temp_binary_data_0[] =
"# HybridApi\n"
"A set of functions that I regularly use. They are designed to be included in a project using Juce. \n"
"\n"
"For most people, ResXmlParser will be the most interesting. It contains functions \n"
"- to get the locations of the various xml files that Resolume uses\n"
"- functions to extract useful data out of these files, for instance\n"
" * comp name\n"
" * comp resolution\n"
" * slice info\n"
" * clip info\n"
" * clip thumbnails\n"
" * osc ip and port\n"
" \n"
" \n";

const char* README_md = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x64791dc8:  numBytes = 432; return README_md;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "README_md"
};

const char* originalFilenames[] =
{
    "README.md"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
