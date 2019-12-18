#pragma once
#include <map>
#include <string>
#include <vector>

const std::wstring Ore = L"ORE";

struct ReactionComponent
{
    int Quantity;
    std::wstring Name;
};

struct Reaction
{
    std::vector<ReactionComponent> Inputs;
    ReactionComponent Output;
};

// Transform with:
// '<,'>s/\(.*\) \(\w\+\)$/    { L"\2", { { \1 \2 } },/ | '<,'>s/\(\d\+\) \(\w\+\)/{ \1, L"\2" }/g | '<,'>s/ =>/ },
const std::map<std::wstring, Reaction> test_data_1 = { {
    { L"A", { { { 10, L"ORE" } }, { 10, L"A" } } },
    { L"B", { { { 1, L"ORE" } }, { 1, L"B" } } },
    { L"C", { { { 7, L"A" }, { 1, L"B" } }, { 1, L"C" } } },
    { L"D", { { { 7, L"A" }, { 1, L"C" } }, { 1, L"D" } } },
    { L"E", { { { 7, L"A" }, { 1, L"D" } }, { 1, L"E" } } },
    { L"FUEL", { { { 7, L"A" }, { 1, L"E" } }, { 1, L"FUEL" } } },
} };


const std::map<std::wstring, Reaction> real_data = { {
    { L"DRKW", { { { 9, L"GJSNW" }, { 9, L"GHJHK" } }, { 6, L"DRKW" } } },
    { L"BFGL", { { { 1, L"SJNKX" }, { 1, L"GHJHK" }, { 7, L"DCPM" } }, { 1, L"BFGL" } } },
    { L"TXWFP", { { { 7, L"RBJHJ" }, { 8, L"CHPCH" }, { 1, L"SJHGH" }, { 9, L"ZMRD" }, { 2, L"VDVN" }, { 17, L"SFSN" }, { 4, L"DPZW" } }, { 9, L"TXWFP" } } },
    { L"QMVN", { { { 1, L"KBJXG" }, { 6, L"GJSNW" }, { 2, L"RKBM" } }, { 9, L"QMVN" } } },
    { L"QZRM", { { { 1, L"QMVN" }, { 1, L"MWXF" } }, { 9, L"QZRM" } } },
    { L"TWNV", { { { 1, L"ZPXS" }, { 1, L"QZRM" } }, { 5, L"TWNV" } } },
    { L"BXGJ", { { { 1, L"RBJHJ" } }, { 9, L"BXGJ" } } },
    { L"KRLSB", { { { 4, L"RFLMC" } }, { 2, L"KRLSB" } } },
    { L"WPXNJ", { { { 9, L"JBTL" }, { 2, L"TZBZR" } }, { 4, L"WPXNJ" } } },
    { L"MWXF", { { { 3, L"DCPM" }, { 2, L"ZTLXS" } }, { 3, L"MWXF" } } },
    { L"SJHGH", { { { 3, L"QXFZ" }, { 3, L"QTZW" } }, { 8, L"SJHGH" } } },
    { L"DXTFP", { { { 15, L"WPXNJ" } }, { 4, L"DXTFP" } } },
    { L"QXFZ", { { { 5, L"ZLJT" }, { 3, L"GHJHK" } }, { 9, L"QXFZ" } } },
    { L"LFQDQ", { { { 2, L"GHJHK" } }, { 8, L"LFQDQ" } } },
    { L"XCLVL", { { { 6, L"QMVN" }, { 19, L"DRKW" } }, { 5, L"XCLVL" } } },
    { L"RPMHX", { { { 5, L"QTZW" }, { 1, L"DCPM" }, { 9, L"KBLFQ" } }, { 6, L"RPMHX" } } },
    { L"TMXRJ", { { { 11, L"KBJXG" } }, { 1, L"TMXRJ" } } },
    { L"SFSN", { { { 4, L"TKNB" } }, { 7, L"SFSN" } } },
    { L"RBJHJ", { { { 29, L"XCLVL" } }, { 6, L"RBJHJ" } } },
    { L"NCNMC", { { { 5, L"BSMN" }, { 11, L"MQZBK" }, { 1, L"XCLVL" }, { 12, L"BXGJ" }, { 2, L"KDHT" }, { 4, L"TMXRJ" } }, { 3, L"NCNMC" } } },
    { L"MQZBK", { { { 1, L"SPKZM" }, { 1, L"TFWDG" }, { 15, L"KRLSB" } }, { 8, L"MQZBK" } } },
    { L"TZBZR", { { { 21, L"DCPM" }, { 18, L"QXFZ" } }, { 2, L"TZBZR" } } },
    { L"KBLFQ", { { { 1, L"TMXRJ" } }, { 3, L"KBLFQ" } } },
    { L"VDVN", { { { 5, L"BCBTD" } }, { 3, L"VDVN" } } },
    { L"DBWNB", { { { 1, L"DXTFP" }, { 15, L"SPKZM" } }, { 5, L"DBWNB" } } },
    { L"QTZW", { { { 5, L"ZTLXS" } }, { 8, L"QTZW" } } },
    { L"JBTL", { { { 4, L"LFQDQ" }, { 1, L"DRKW" } }, { 5, L"JBTL" } } },
    { L"KDFC", { { { 6, L"XCLVL" } }, { 6, L"KDFC" } } },
    { L"CXZG", { { { 2, L"TWNV" }, { 29, L"CRDZ" } }, { 9, L"CXZG" } } },
    { L"ZMRD", { { { 11, L"KQVSV" }, { 5, L"KSNJ" } }, { 7, L"ZMRD" } } },
    { L"RKBM", { { { 150, L"ORE" } }, { 3, L"RKBM" } } },
    { L"SJNKX", { { { 9, L"QXFZ" }, { 3, L"JBTL" } }, { 1, L"SJNKX" } } },
    { L"FUEL", { { { 8, L"TXWFP" }, { 1, L"BSMN" }, { 6, L"WRTCX" }, { 5, L"NCNMC" }, { 12, L"RPMHX" }, { 18, L"VZNQ" }, { 1, L"ZPXS" }, { 17, L"MGWHP" }, { 15, L"CXZG" } }, { 1, L"FUEL" } } },
    { L"WRTCX", { { { 14, L"SJHGH" }, { 1, L"KQVSV" }, { 12, L"BCBTD" }, { 17, L"QLQP" }, { 11, L"JBLCQ" }, { 2, L"KDHT" }, { 2, L"JBTL" } }, { 9, L"WRTCX" } } },
    { L"SPKZM", { { { 2, L"TKNB" }, { 11, L"KDFC" } }, { 9, L"SPKZM" } } },
    { L"WXRBN", { { { 122, L"ORE" } }, { 7, L"WXRBN" } } },
    { L"ZPXS", { { { 16, L"TZBZR" } }, { 1, L"ZPXS" } } },
    { L"QLQP", { { { 2, L"KDHT" } }, { 5, L"QLQP" } } },
    { L"ZLJT", { { { 3, L"RKBM" }, { 5, L"WXRBN" } }, { 6, L"ZLJT" } } },
    { L"TKNB", { { { 26, L"MWXF" }, { 6, L"MCXDR" } }, { 2, L"TKNB" } } },
    { L"MCXDR", { { { 2, L"SJNKX" } }, { 5, L"MCXDR" } } },
    { L"DCPM", { { { 2, L"QXFZ" } }, { 8, L"DCPM" } } },
    { L"TFWDG", { { { 2, L"KBLFQ" } }, { 7, L"TFWDG" } } },
    { L"GHJHK", { { { 172, L"ORE" } }, { 9, L"GHJHK" } } },
    { L"CRDZ", { { { 2, L"CHPCH" }, { 8, L"DPZW" }, { 11, L"ZLJT" } }, { 2, L"CRDZ" } } },
    { L"CHPCH", { { { 2, L"SPKZM" }, { 6, L"DCPM" } }, { 4, L"CHPCH" } } },
    { L"MGWHP", { { { 9, L"RPMHX" }, { 5, L"KQVSV" } }, { 9, L"MGWHP" } } },
    { L"KSNJ", { { { 3, L"BFGL" }, { 5, L"WPXNJ" } }, { 9, L"KSNJ" } } },
    { L"DPZW", { { { 1, L"SJGC" } }, { 8, L"DPZW" } } },
    { L"BCBTD", { { { 1, L"BSMN" } }, { 5, L"BCBTD" } } },
    { L"SJGC", { { { 2, L"ZTLXS" }, { 1, L"KSNJ" } }, { 8, L"SJGC" } } },
    { L"GJSNW", { { { 186, L"ORE" } }, { 8, L"GJSNW" } } },
    { L"KDHT", { { { 20, L"TKNB" }, { 1, L"DXTFP" }, { 11, L"QZRM" } }, { 7, L"KDHT" } } },
    { L"BSMN", { { { 14, L"DXTFP" } }, { 7, L"BSMN" } } },
    { L"KBJXG", { { { 117, L"ORE" } }, { 6, L"KBJXG" } } },
    { L"VZNQ", { { { 2, L"WPXNJ" } }, { 4, L"VZNQ" } } },
    { L"RFLMC", { { { 4, L"RPFV" }, { 1, L"ZMRD" } }, { 4, L"RFLMC" } } },
    { L"RPFV", { { { 10, L"QTZW" } }, { 2, L"RPFV" } } },
    { L"ZTLXS", { { { 2, L"QMVN" }, { 6, L"LFQDQ" }, { 7, L"GJSNW" } }, { 7, L"ZTLXS" } } },
    { L"KQVSV", { { { 33, L"QZRM" } }, { 4, L"KQVSV" } } },
    { L"JBLCQ", { { { 1, L"SJHGH" }, { 1, L"DPZW" }, { 8, L"DBWNB" } }, { 8, L"JBLCQ" } } },
} };
