#include "startup/math_dispatch_state.h"

// Actual original function entry symbols; byte-array declarations bind
// addresses without pretending unknown C++ argument/return signatures.
// Decorated stack bytes are proved from original reachable RET paths.
extern "C" {
extern const unsigned char code_005e3c1d[] __asm__("_FUN_005e3c1d@12");
extern const unsigned char code_005e3c36[] __asm__("_FUN_005e3c36@12");
extern const unsigned char code_005e3cd8[] __asm__("_FUN_005e3cd8@12");
extern const unsigned char code_005e3cf1[] __asm__("_FUN_005e3cf1@12");
extern const unsigned char code_005e3d98[] __asm__("_FUN_005e3d98@8");
extern const unsigned char code_005e3db1[] __asm__("_FUN_005e3db1@24");
extern const unsigned char code_005e3ddd[] __asm__("_FUN_005e3ddd@24");
extern const unsigned char code_005e3e6d[] __asm__("_FUN_005e3e6d@24");
extern const unsigned char code_005e3e99[] __asm__("_FUN_005e3e99@24");
extern const unsigned char code_005e3f4a[] __asm__("_FUN_005e3f4a@24");
extern const unsigned char code_005e3f7b[] __asm__("_FUN_005e3f7b@24");
extern const unsigned char code_005e3fc0[] __asm__("_FUN_005e3fc0@12");
extern const unsigned char code_005e3fd9[] __asm__("_FUN_005e3fd9@24");
extern const unsigned char code_005e3fec[] __asm__("_FUN_005e3fec@12");
extern const unsigned char code_005e4005[] __asm__("_FUN_005e4005@24");
extern const unsigned char code_005e4018[] __asm__("_FUN_005e4018@12");
extern const unsigned char code_005e4031[] __asm__("_FUN_005e4031@12");
extern const unsigned char code_005e406f[] __asm__("_FUN_005e406f@24");
extern const unsigned char code_005e4082[] __asm__("_FUN_005e4082@24");
extern const unsigned char code_005e40d8[] __asm__("_FUN_005e40d8@8");
extern const unsigned char code_005e40f1[] __asm__("_FUN_005e40f1@24");
extern const unsigned char code_005e411d[] __asm__("_FUN_005e411d@24");
extern const unsigned char code_005e41cd[] __asm__("_FUN_005e41cd@24");
extern const unsigned char code_005e41f9[] __asm__("_FUN_005e41f9@24");
extern const unsigned char code_005e42cc[] __asm__("_FUN_005e42cc@24");
extern const unsigned char code_005e42fd[] __asm__("_FUN_005e42fd@24");
extern const unsigned char code_005e435c[] __asm__("_FUN_005e435c@12");
extern const unsigned char code_005e4375[] __asm__("_FUN_005e4375@12");
extern const unsigned char code_005e4402[] __asm__("_FUN_005e4402@24");
extern const unsigned char code_005e4415[] __asm__("_FUN_005e4415@24");
extern const unsigned char code_005e44be[] __asm__("_FUN_005e44be@12");
extern const unsigned char code_005e44d7[] __asm__("_FUN_005e44d7@24");
extern const unsigned char code_005e44f0[] __asm__("_FUN_005e44f0@24");
extern const unsigned char code_005e45d1[] __asm__("_FUN_005e45d1@12");
extern const unsigned char code_005e45ea[] __asm__("_FUN_005e45ea@12");
extern const unsigned char code_005e4652[] __asm__("_FUN_005e4652@24");
extern const unsigned char code_005e4665[] __asm__("_FUN_005e4665@24");
extern const unsigned char code_005e46e5[] __asm__("_FUN_005e46e5@24");
extern const unsigned char code_005e46fe[] __asm__("_FUN_005e46fe@36");
extern const unsigned char code_005e4711[] __asm__("_FUN_005e4711@24");
extern const unsigned char code_005e4724[] __asm__("_FUN_005e4724@36");
extern const unsigned char code_005e4737[] __asm__("_FUN_005e4737@16");
extern const unsigned char code_005e474a[] __asm__("_FUN_005e474a@16");
extern const unsigned char code_005e483c[] __asm__("_FUN_005e483c@8");
extern const unsigned char code_005e4855[] __asm__("_FUN_005e4855@24");
extern const unsigned char code_005e4881[] __asm__("_FUN_005e4881@24");
extern const unsigned char code_005e4954[] __asm__("_FUN_005e4954@24");
extern const unsigned char code_005e4980[] __asm__("_FUN_005e4980@24");
extern const unsigned char code_005e4a75[] __asm__("_FUN_005e4a75@24");
extern const unsigned char code_005e4aa6[] __asm__("_FUN_005e4aa6@24");
extern const unsigned char code_005e4b1f[] __asm__("_FUN_005e4b1f@12");
extern const unsigned char code_005e4b38[] __asm__("_FUN_005e4b38@12");
extern const unsigned char code_005e4bd9[] __asm__("_FUN_005e4bd9@24");
extern const unsigned char code_005e4bec[] __asm__("_FUN_005e4bec@24");
extern const unsigned char code_005e4cad[] __asm__("_FUN_005e4cad@4");
extern const unsigned char code_005e4cc6[] __asm__("_FUN_005e4cc6@4");
extern const unsigned char code_005e4d92[] __asm__("_FUN_005e4d92@16");
extern const unsigned char code_005e4da5[] __asm__("_FUN_005e4da5@12");
extern const unsigned char code_005e4dbe[] __asm__("_FUN_005e4dbe@12");
extern const unsigned char code_005e4ff6[] __asm__("_FUN_005e4ff6@8");
extern const unsigned char code_005e500f[] __asm__("_FUN_005e500f@8");
extern const unsigned char code_005e5080[] __asm__("_FUN_005e5080@12");
extern const unsigned char code_005e5093[] __asm__("_FUN_005e5093@12");
extern const unsigned char code_005e52cb[] __asm__("_FUN_005e52cb@12");
extern const unsigned char code_005e52e4[] __asm__("_FUN_005e52e4@12");
extern const unsigned char code_005e568b[] __asm__("_FUN_005e568b@16");
extern const unsigned char code_005e56c1[] __asm__("_FUN_005e56c1@16");
extern const unsigned char code_005e571f[] __asm__("_FUN_005e571f@16");
extern const unsigned char code_005e5755[] __asm__("_FUN_005e5755@16");
extern const unsigned char code_005e57b3[] __asm__("_FUN_005e57b3@8");
extern const unsigned char code_005e57d9[] __asm__("_FUN_005e57d9@8");
extern const unsigned char code_005e5855[] __asm__("_FUN_005e5855@8");
extern const unsigned char code_005e587b[] __asm__("_FUN_005e587b@8");
extern const unsigned char code_005e58f8[] __asm__("_FUN_005e58f8@8");
extern const unsigned char code_005e591e[] __asm__("_FUN_005e591e@8");
extern const unsigned char code_005e599c[] __asm__("_FUN_005e599c@12");
extern const unsigned char code_005e59c5[] __asm__("_FUN_005e59c5@12");
extern const unsigned char code_005e5ac6[] __asm__("_FUN_005e5ac6@8");
extern const unsigned char code_005e5adf[] __asm__("_FUN_005e5adf@8");
extern const unsigned char code_005e5bc3[] __asm__("_FUN_005e5bc3@16");
extern const unsigned char code_005e5bf3[] __asm__("_FUN_005e5bf3@28");
extern const unsigned char code_005e5c06[] __asm__("_FUN_005e5c06@28");
extern const unsigned char code_005e5f12[] __asm__("_FUN_005e5f12@28");
extern const unsigned char code_005e5f45[] __asm__("_FUN_005e5f45@28");
extern const unsigned char code_005e623e[] __asm__("_FUN_005e623e@20");
extern const unsigned char code_005e6267[] __asm__("_FUN_005e6267@20");
extern const unsigned char code_005e6357[] __asm__("_FUN_005e6357@20");
extern const unsigned char code_005e6384[] __asm__("_FUN_005e6384@20");
extern const unsigned char code_005e66ff[] __asm__("_FUN_005e66ff@12");
extern const unsigned char code_005e6712[] __asm__("_FUN_005e6712@8");
extern const unsigned char code_005e6725[] __asm__("_FUN_005e6725@12");
extern const unsigned char code_005e6738[] __asm__("_FUN_005e6738@12");
extern const unsigned char code_005e6770[] __asm__("_FUN_005e6770@8");
extern const unsigned char code_005e6789[] __asm__("_FUN_005e6789@8");
extern const unsigned char code_005e68bf[] __asm__("_FUN_005e68bf@12");
extern const unsigned char code_005e68e2[] __asm__("_FUN_005e68e2@12");
extern const unsigned char code_005e6940[] __asm__("_FUN_005e6940@16");
extern const unsigned char code_005e6976[] __asm__("_FUN_005e6976@16");
extern const unsigned char code_005e6a51[] __asm__("_FUN_005e6a51@12");
extern const unsigned char code_005e6a6a[] __asm__("_FUN_005e6a6a@12");
extern const unsigned char code_005e6b02[] __asm__("_FUN_005e6b02@8");
extern const unsigned char code_005e6b15[] __asm__("_FUN_005e6b15@8");
extern const unsigned char code_005e6b2e[] __asm__("_FUN_005e6b2e@8");
extern const unsigned char code_005e6be1[] __asm__("_FUN_005e6be1@8");
extern const unsigned char code_005e6bfa[] __asm__("_FUN_005e6bfa@8");
extern const unsigned char code_005e6c77[] __asm__("_FUN_005e6c77@8");
extern const unsigned char code_005e6c90[] __asm__("_FUN_005e6c90@8");
extern const unsigned char code_005e6d2a[] __asm__("_FUN_005e6d2a@16");
extern const unsigned char code_005e6d56[] __asm__("_FUN_005e6d56@16");
extern const unsigned char code_005e6e3b[] __asm__("_FUN_005e6e3b@24");
extern const unsigned char code_005e6e67[] __asm__("_FUN_005e6e67@24");
extern const unsigned char code_005e6ec0[] __asm__("_FUN_005e6ec0@28");
extern const unsigned char code_005e6ed3[] __asm__("_FUN_005e6ed3@24");
extern const unsigned char code_005e6f04[] __asm__("_FUN_005e6f04@24");
extern const unsigned char code_005e6f8e[] __asm__("_FUN_005e6f8e@8");
extern const unsigned char code_005e6fa7[] __asm__("_FUN_005e6fa7@8");
extern const unsigned char code_005e704a[] __asm__("_FUN_005e704a@16");
extern const unsigned char code_005e705d[] __asm__("_FUN_005e705d@16");
extern const unsigned char code_005e7113[] __asm__("_FUN_005e7113@12");
extern const unsigned char code_005e7126[] __asm__("_FUN_005e7126@12");
extern const unsigned char code_005e7161[] __asm__("_FUN_005e7161@16");
extern const unsigned char code_005e717a[] __asm__("_FUN_005e717a@16");
extern const unsigned char code_005e721e[] __asm__("_FUN_005e721e@12");
extern const unsigned char code_005e7231[] __asm__("_FUN_005e7231@12");
extern const unsigned char code_005e72d2[] __asm__("_FUN_005e72d2@24");
extern const unsigned char code_005e72e5[] __asm__("_FUN_005e72e5@24");
extern const unsigned char code_005e7611[] __asm__("_FUN_005e7611@44");
extern const unsigned char code_005e7624[] __asm__("_FUN_005e7624@32");
extern const unsigned char code_005e7637[] __asm__("_FUN_005e7637@8");
extern const unsigned char code_005e76c3[] __asm__("_FUN_005e76c3@12");
extern const unsigned char code_005e7730[] __asm__("_FUN_005e7730@24");
extern const unsigned char code_005e77b5[] __asm__("_FUN_005e77b5@12");
extern const unsigned char code_005e7834[] __asm__("_FUN_005e7834@24");
extern const unsigned char code_005e78ce[] __asm__("_FUN_005e78ce@8");
extern const unsigned char code_005e796d[] __asm__("_FUN_005e796d@12");
extern const unsigned char code_005e7a2b[] __asm__("_FUN_005e7a2b@24");
extern const unsigned char code_005e7bb5[] __asm__("_FUN_005e7bb5@36");
extern const unsigned char code_005e7da2[] __asm__("_FUN_005e7da2@24");
extern const unsigned char code_005e7f41[] __asm__("_FUN_005e7f41@36");
extern const unsigned char code_005e815a[] __asm__("_FUN_005e815a@8");
extern const unsigned char code_005e8212[] __asm__("_FUN_005e8212@16");
extern const unsigned char code_005e85a2[] __asm__("_FUN_005e85a2@16");
extern const unsigned char code_005e85dd[] __asm__("_FUN_005e85dd@12");
extern const unsigned char code_005e86db[] __asm__("_FUN_005e86db@8");
extern const unsigned char code_005e879c[] __asm__("_FUN_005e879c@28");
extern const unsigned char code_005fc8ac[] __asm__("_FUN_005fc8ac@44");
extern const unsigned char code_005fccc5[] __asm__("_FUN_005fccc5@32");
extern const unsigned char code_0064f179[] __asm__("_FUN_0064f179@12");
extern const unsigned char code_0064f1e4[] __asm__("_FUN_0064f1e4@12");
extern const unsigned char code_0064f21b[] __asm__("_FUN_0064f21b@12");
extern const unsigned char code_0064f2a8[] __asm__("_FUN_0064f2a8@12");
extern const unsigned char code_0064f309[] __asm__("_FUN_0064f309@12");
extern const unsigned char code_0064f3e9[] __asm__("_FUN_0064f3e9@8");
extern const unsigned char code_0064f4b5[] __asm__("_FUN_0064f4b5@12");
extern const unsigned char code_0064f59a[] __asm__("_FUN_0064f59a@12");
}

extern "C" D3dxDispatchTable dat_0070f370 = {{
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3fc0)), // slot00, original0x0070f370
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e435c)), // slot01, original0x0070f374
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4b1f)), // slot02, original0x0070f378
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4da5)), // slot03, original0x0070f37c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e5080)), // slot04, original0x0070f380
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4018)), // slot05, original0x0070f384
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e45d1)), // slot06, original0x0070f388
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e40d8)), // slot07, original0x0070f38c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e483c)), // slot08, original0x0070f390
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3fec)), // slot09, original0x0070f394
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e44be)), // slot10, original0x0070f398
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4cad)), // slot11, original0x0070f39c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4d92)), // slot12, original0x0070f3a0
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7113)), // slot13, original0x0070f3a4
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7161)), // slot14, original0x0070f3a8
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e46e5)), // slot15, original0x0070f3ac
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4711)), // slot16, original0x0070f3b0
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4737)), // slot17, original0x0070f3b4
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3db1)), // slot18, original0x0070f3b8
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e52cb)), // slot19, original0x0070f3bc
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6a51)), // slot20, original0x0070f3c0
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6b02)), // slot21, original0x0070f3c4
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6f8e)), // slot22, original0x0070f3c8
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e704a)), // slot23, original0x0070f3cc
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6725)), // slot24, original0x0070f3d0
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6770)), // slot25, original0x0070f3d4
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6940)), // slot26, original0x0070f3d8
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e571f)), // slot27, original0x0070f3dc
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e66ff)), // slot28, original0x0070f3e0
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6712)), // slot29, original0x0070f3e4
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e68bf)), // slot30, original0x0070f3e8
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e57b3)), // slot31, original0x0070f3ec
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e5855)), // slot32, original0x0070f3f0
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e58f8)), // slot33, original0x0070f3f4
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e568b)), // slot34, original0x0070f3f8
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e721e)), // slot35, original0x0070f3fc
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6d2a)), // slot36, original0x0070f400
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6ed3)), // slot37, original0x0070f404
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4ff6)), // slot38, original0x0070f408
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e5ac6)), // slot39, original0x0070f40c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e5bf3)), // slot40, original0x0070f410
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e5bc3)), // slot41, original0x0070f414
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e623e)), // slot42, original0x0070f418
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e599c)), // slot43, original0x0070f41c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6e3b)), // slot44, original0x0070f420
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6b15)), // slot45, original0x0070f424
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6ec0)), // slot46, original0x0070f428
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3d98)), // slot47, original0x0070f42c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3e6d)), // slot48, original0x0070f430
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3f4a)), // slot49, original0x0070f434
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e40f1)), // slot50, original0x0070f438
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e41cd)), // slot51, original0x0070f43c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e42cc)), // slot52, original0x0070f440
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4855)), // slot53, original0x0070f444
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4954)), // slot54, original0x0070f448
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4a75)), // slot55, original0x0070f44c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6be1)), // slot56, original0x0070f450
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6c77)), // slot57, original0x0070f454
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3c1d)), // slot58, original0x0070f458
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3cd8)), // slot59, original0x0070f45c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3fd9)), // slot60, original0x0070f460
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4005)), // slot61, original0x0070f464
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e406f)), // slot62, original0x0070f468
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4402)), // slot63, original0x0070f46c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e44d7)), // slot64, original0x0070f470
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4652)), // slot65, original0x0070f474
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4bd9)), // slot66, original0x0070f478
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e46fe)), // slot67, original0x0070f47c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4724)), // slot68, original0x0070f480
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e72d2)), // slot69, original0x0070f484
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7611)), // slot70, original0x0070f488
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7624)), // slot71, original0x0070f48c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e5f12)), // slot72, original0x0070f490
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6357)), // slot73, original0x0070f494
}};

extern "C" D3dxDispatchTable dat_0070f498 = {{
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e76c3)), // slot00, original0x0070f370
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4375)), // slot01, original0x0070f374
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4b38)), // slot02, original0x0070f378
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4dbe)), // slot03, original0x0070f37c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e5093)), // slot04, original0x0070f380
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4031)), // slot05, original0x0070f384
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e45ea)), // slot06, original0x0070f388
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e78ce)), // slot07, original0x0070f38c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e815a)), // slot08, original0x0070f390
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e77b5)), // slot09, original0x0070f394
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e796d)), // slot10, original0x0070f398
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4cc6)), // slot11, original0x0070f39c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e8212)), // slot12, original0x0070f3a0
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7126)), // slot13, original0x0070f3a4
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e717a)), // slot14, original0x0070f3a8
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7a2b)), // slot15, original0x0070f3ac
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7da2)), // slot16, original0x0070f3b0
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e474a)), // slot17, original0x0070f3b4
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3ddd)), // slot18, original0x0070f3b8
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e52e4)), // slot19, original0x0070f3bc
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6a6a)), // slot20, original0x0070f3c0
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e815a)), // slot21, original0x0070f3c4
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6fa7)), // slot22, original0x0070f3c8
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e705d)), // slot23, original0x0070f3cc
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6738)), // slot24, original0x0070f3d0
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6789)), // slot25, original0x0070f3d4
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6976)), // slot26, original0x0070f3d8
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e5755)), // slot27, original0x0070f3dc
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e85dd)), // slot28, original0x0070f3e0
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e86db)), // slot29, original0x0070f3e4
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e68e2)), // slot30, original0x0070f3e8
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e57d9)), // slot31, original0x0070f3ec
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e587b)), // slot32, original0x0070f3f0
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e591e)), // slot33, original0x0070f3f4
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e56c1)), // slot34, original0x0070f3f8
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7231)), // slot35, original0x0070f3fc
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6d56)), // slot36, original0x0070f400
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6f04)), // slot37, original0x0070f404
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e500f)), // slot38, original0x0070f408
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e5adf)), // slot39, original0x0070f40c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e5c06)), // slot40, original0x0070f410
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e85a2)), // slot41, original0x0070f414
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6267)), // slot42, original0x0070f418
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e59c5)), // slot43, original0x0070f41c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6e67)), // slot44, original0x0070f420
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6b2e)), // slot45, original0x0070f424
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e879c)), // slot46, original0x0070f428
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7637)), // slot47, original0x0070f42c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3e99)), // slot48, original0x0070f430
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3f7b)), // slot49, original0x0070f434
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e411d)), // slot50, original0x0070f438
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e41f9)), // slot51, original0x0070f43c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e42fd)), // slot52, original0x0070f440
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4881)), // slot53, original0x0070f444
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4980)), // slot54, original0x0070f448
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4aa6)), // slot55, original0x0070f44c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6bfa)), // slot56, original0x0070f450
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6c90)), // slot57, original0x0070f454
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3c36)), // slot58, original0x0070f458
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e3cf1)), // slot59, original0x0070f45c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7730)), // slot60, original0x0070f460
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7834)), // slot61, original0x0070f464
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4082)), // slot62, original0x0070f468
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4415)), // slot63, original0x0070f46c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e44f0)), // slot64, original0x0070f470
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4665)), // slot65, original0x0070f474
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e4bec)), // slot66, original0x0070f478
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7bb5)), // slot67, original0x0070f47c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e7f41)), // slot68, original0x0070f480
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e72e5)), // slot69, original0x0070f484
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005fc8ac)), // slot70, original0x0070f488
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005fccc5)), // slot71, original0x0070f48c
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e5f45)), // slot72, original0x0070f490
    reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_005e6384)), // slot73, original0x0070f494
}};

extern "C" uint32_t dat_0070ff04 = 0x0000ffff;

extern "C" D3dxDispatchTable* __attribute__((stdcall)) FUN_0064f62a(D3dxDispatchTable* table) {
    table->entries[0] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0064f179)); // original0x0064f637
    table->entries[1] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0064f21b)); // original0x0064f63d
    table->entries[2] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0064f309)); // original0x0064f644
    table->entries[3] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0064f4b5)); // original0x0064f647
    table->entries[4] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0064f59a)); // original0x0064f64e
    table->entries[5] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0064f1e4)); // original0x0064f655
    table->entries[6] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0064f2a8)); // original0x0064f65c
    table->entries[7] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0064f3e9)); // original0x0064f663
    table->entries[35] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0064f309)); // original0x0064f66a
    return table;                                   // Original retains its incoming pointer in EAX.
}
