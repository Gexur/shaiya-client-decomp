// Exact original0040b1f0 deleting wrapper and0040b210 destructor.
extern "C" __attribute__((naked, used)) void FUN_0040b1f0() {
    __asm__ volatile(".intel_syntax noprefix\n"
                     "push esi\nmov esi,ecx\ncall _FUN_0040b210\n"
                     "test byte ptr [esp+8],1\nje 1f\npush esi\ncall _fun_005cc620\nadd esp,4\n"
                     "1: mov eax,esi\npop esi\nret 4\n.att_syntax prefix\n");
}
extern "C" __attribute__((naked, used)) void FUN_0040b210() {
    __asm__ volatile(
        ".intel_syntax noprefix\n"
        "push esi\nmov esi,ecx\nmov eax,[esi+0x240]\ntest eax,eax\n"
        "mov dword ptr [esi],offset _dat_006bbd68\nje 1f\npush eax\ncall _fun_005cc620\nadd esp,4\n"
        "mov dword ptr [esi+0x240],0\n1: lea ecx,[esi+0x488]\npop esi\njmp _FUN_0040ade0\n.att_syntax prefix\n");
}
