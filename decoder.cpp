#include <iostream>
#include "elfio/elfio.hpp"
#include "instruction.hpp" // استدعاء هيكل التعليمة الذي برمجته

using namespace std;
using namespace ELFIO;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <elf_file_path>\n";
        return 1; 
    }

    elfio reader; 
    if (!reader.load(argv[1])) {
        cerr << "Error: Cannot open or read ELF file: " << argv[1] << "\n";
        return 1;
    }

    section* text_section = reader.sections[".text"];
    if (text_section == nullptr) {
        cerr << "Error: No .text section found in the ELF file!\n";
        return 1;
    }
    
    const char* data = text_section->get_data();
    Elf_Xword size = text_section->get_size();
    Elf64_Addr start_address = text_section->get_address(); 

    cout << "Successfully loaded .text section. Size: " << size << " bytes.\n\n";

    for (Elf_Xword i = 0; i < size; i += 4) {
        uint32_t inst_val = *reinterpret_cast<const uint32_t*>(data + i);
        uint32_t current_address = start_address + i;
        
        // إنشاء كائن التعليمة وفك التشفير والطباعة
        Instruction my_inst;
        my_inst.decode(inst_val, current_address);
        my_inst.print();
    }

    return 0;
}