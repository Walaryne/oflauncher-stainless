//
// Created by fenteale on 11/11/20.
//

#include "OFSGameInfo.h"

namespace fs=std::experimental::filesystem;

const std::string giTop =
	"\"GameInfo\"\n"
	"{\n"
	"\tgame \t\t\t\"Open Fortress\"\n"
	"\ttitle \t\t\t\"\"\n"
	"\ttitle2\t\t\t\"\"\t\n"
	"\tgamelogo\t\t\"1\"\n"
	"\tdeveloper\t\t\"https://github.com/AgitationSkeleton/open_fortress/blob/master/credits.txt\"\n"
	"\tdeveloper_url\t\"https://github.com/KaidemonLP/Open-Fortress-Source\"\n"
	"\tmanual\t\t\t\"\"\n"
	"\t\n"
	"\ttype\t\t\t\"multiplayer_only\"\n"
	"\thasportals\t\t\"0\" // gameui.dll\n"
	"\thashdcontent\t\"0\" // gameui.dll\n"
	"\tnomodels\t\t\"0\" // gameui.dll\n"
	"\tnohimodel\t\t\"0\" // gameui.dll\n"
	"\tnocrosshair\t\t\"0\" // gameui.dll\n"
	"\tadvcrosshair \t\"1\" // gameui.dll\n"
	"\tnodifficulty\t\"1\" // gameui.dll\n"
	"\tsupportsvr\t\t\"0\" // engine.dll + gameui.dll\n"
	"\tbots\t\t\t\"0\" // gameui.dll\n"
	"\tnodegraph\t\t\"1\" // engine.dll\n"
	"\tperfwizard\t\t\"0\" // unused\n"
	"\tSupportsDX8\t\t\"0\" // unused\n"
	"\tSupportsDX9\t\t\"1\" // unused\n"
	"\tSupportsDX10\t\"0\" // unused\n"
	"\tSupportsDX11\t\"0\" // unused\n"
	"\tSupportsXbox\t\"0\" // unused\n"
	"\tSupportsXbox360\t\"0\" // unused\n"
	"\tSupportsXboxOne\t\"0\" // unused\n"
	"\tSupportsPS3\t\t\"0\" // unused\n"
	"\tSupportsPS4\t\t\"0\" // unused\n"
	"\ticon\t\t\t\"resource/game\"\n"
	"\tGameData\t\t\"ofd_fic2.fgd\"\n"
	"\tInstancePath\t\"maps/instances/\"\n"
	"\t\n"
	"\thidden_maps\n"
	"\t{\n"
	"\t\t\"test_speakers\"\t\t1\n"
	"\t\t\"test_hardware\"\t\t1\n"
	"        \"background01\"\t\t1\n"
	"        \"background02\"\t\t1\n"
	"        \"background03\"\t\t1\n"
	"        \"background04\"\t\t1\n"
	"        \"background05\"\t\t1\n"
	"        \"background06\"\t\t1\n"
	"        \"background07\"\t\t1\n"
	"        \"background08\"\t\t1\n"
	"        \"background09\"\t\t1\n"
	"        \"background12\"\t\t1\n"
	"        \"background15\"\t\t1\n"
	"\t\t\"ep1_c17_00\"\t\t1\n"
	"\t\t\"ep1_c17_00a\"\t\t1\n"
	"\t\t\"ep1_c17_01\"\t\t1\n"
	"\t\t\"ep1_c17_01a\"\t\t1\n"
	"\t\t\"ep1_c17_02\"\t\t1\n"
	"\t\t\"ep1_c17_02a\"\t\t1\n"
	"\t\t\"ep1_c17_02b\"\t\t1\n"
	"\t\t\"ep1_c17_05\"\t\t1\n"
	"\t\t\"ep1_c17_06\"\t\t1\n"
	"\t\t\"ep1_citadel_00\"\t1\n"
	"\t\t\"ep1_citadel_00_demo\" 1\n"
	"\t\t\"ep1_citadel_01\"\t1\n"
	"\t\t\"ep1_citadel_02\"\t1\n"
	"\t\t\"ep1_citadel_02b\"\t1\n"
	"\t\t\"ep1_citadel_03\"\t1\n"
	"\t\t\"ep1_citadel_04\"\t1\n"
	"\t\t\"ep1_background01\"\t1\n"
	"\t\t\"ep1_background01a\"\t1\n"
	"\t\t\"ep1_background02\"\t1\n"
	"\t\t\"ep2_outland_01\"\t1\n"
	"\t\t\"ep2_outland_01a\"\t1\n"
	"\t\t\"ep2_outland_02\"\t1\n"
	"\t\t\"ep2_outland_03\"\t1\n"
	"\t\t\"ep2_outland_04\"\t1\n"
	"\t\t\"ep2_outland_05\"\t1\n"
	"\t\t\"ep2_outland_06\"\t1\n"
	"\t\t\"ep2_outland_06a\"\t1\n"
	"\t\t\"ep2_outland_07\"\t1\n"
	"\t\t\"ep2_outland_08\"\t1\n"
	"\t\t\"ep2_outland_09\"\t1\n"
	"\t\t\"ep2_outland_10\"\t1\n"
	"\t\t\"ep2_outland_10a\"\t1\n"
	"\t\t\"ep2_outland_11\"\t1\n"
	"\t\t\"ep2_outland_11a\"\t1\n"
	"\t\t\"ep2_outland_11b\"\t1\n"
	"\t\t\"ep2_outland_12\"\t1\n"
	"\t\t\"ep2_outland_12a\"\t1\n"
	"\t\t\"ep2_background01\"\t1\n"
	"\t\t\"ep2_background02\"\t1\n"
	"\t\t\"ep2_background02a\"\t1\n"
	"\t\t\"ep2_background03\"\t1\n"
	"\t\t\"credits\"\t\t\t1\n"
	"\t\t\"vst_lostcoast\"\t\t1\n"
	"        \"test\"\t\t\t\t1\n"
	"\t\t\"sdk_vehicles\"\t\t1\n"
	"\t}\n"
	"\t\n"
	"\tFileSystem\n"
	"\t{\n"
	"\t\tSteamAppId\t\t\t\t243750\n"
	"\t\t\n"
	"\t\tSearchPaths\n"
	"\t\t{\n"
	"\t\t\tgame+mod\t\t\t|gameinfo_path|custom/*\n"
	"\t\t\tgame+game_write+mod+mod_write+default_write_path |gameinfo_path|.\n"
	"\t\t\tgamebin\t\t\t\t|gameinfo_path|bin\n"
	"\t\t\t\n"
	"\t\t\t// The lines below until the BREAK comment are responsible for the game resources to work properly\n"
	"\t\t\t// in Hammer and other Source tools. The default setup assumes that you have everything (Steam, TF2,\n"
	"\t\t\t// Source SDK and OF) in the same drive letter/partition. If you have a different storage configuration,\n"
	"\t\t\t// feel free to modify the paths below between quotes (example: D:\\Steam\\steamapps\\common\\Team Fortress 2\\tf).\n";
/*
	"\t\t\tgame\t\t\t\t\"|all_source_engine_paths|..\\Team Fortress 2\\tf\\tf2_misc.vpk\"\n"
	"\t\t\tgame\t\t\t\t\"|all_source_engine_paths|..\\Team Fortress 2\\tf\\tf2_sound_misc.vpk\"\n"
	"\t\t\tgame\t\t\t\t\"|all_source_engine_paths|..\\Team Fortress 2\\tf\\tf2_sound_vo_english.vpk\"\n"
	"\t\t\tgame\t\t\t\t\"|all_source_engine_paths|..\\Team Fortress 2\\tf\\tf2_textures.vpk\"\n"
	"\t\t\tgame\t\t\t\t\"|all_source_engine_paths|..\\Team Fortress 2\\tf\"\n"
	"\t\t\t\n"
	"\t\t\tgame\t\t\t\t\"|all_source_engine_paths|..\\Team Fortress 2\\hl2\\hl2_textures.vpk\"\n"
	"\t\t\tgame\t\t\t\t\"|all_source_engine_paths|..\\Team Fortress 2\\hl2\\hl2_sound_vo_english.vpk\"\n"
	"\t\t\tgame\t\t\t\t\"|all_source_engine_paths|..\\Team Fortress 2\\hl2\\hl2_sound_misc.vpk\"\n"
	"\t\t\t\n"
 */
const std::string giBot =
	"\t\t\t// The hl2 folder here is from Source SDK Base 2013 Multiplayer.\n"
	"\t\t\tgame\t\t\t\t\"|all_source_engine_paths|hl2\\hl2_misc.vpk\"\n"
	"\t\t\tgame\t\t\t\t\"|all_source_engine_paths|hl2\"\n"
	"\t\t\t// ========== BREAK ==========\n"
	"\t\t\t\n"
	"\t\t\tplatform\t\t\t|all_source_engine_paths|platform/platform_misc.vpk\n"
	"\t\t\tplatform\t\t\t|all_source_engine_paths|platform\n"
	"\t\t\t\n"
	"\t\t\tgame+download\t\t|gameinfo_path|download\n"
	"\t\t\t\n"
	"\t\t}\n"
	"\t}\n"
	"}";

void writeGameInfo(fs::path giPath, OFSSteam* steam) {
	fs::path tfFullPath 			=steam->getApp(440)->getInstallPath();
	fs::path tf						=tfFullPath / "tf";
	fs::path tf_misc				=tf / "tf2_misc.vpk";
	fs::path tf_sound_misc			=tf / "tf2_sound_misc.vpk";
	fs::path tf_sound_vo_english	=tf / "tf2_sound_vo_english.vpk";
	fs::path tf_textures			=tf / "tf2_textures";

	fs::path hl2_textures			=tfFullPath / "hl2" / "hl2_textures.vpk";
	fs::path hl2_sound_vo_english	=tfFullPath / "hl2" / "hl2_sound_vo_english.vpk";
	fs::path hl2_sound_misc			=tfFullPath / "hl2" / "hl2_sound_misc.vpk";


	std::ofstream gi(giPath / "gameinfo.txt", std::ios::out | std::ios::trunc);

	gi << giTop;

	gi << "\t\t\tgame\t\t\t\t\"" << tf_misc.string() << "\"" << std::endl;
	gi << "\t\t\tgame\t\t\t\t\"" << tf_sound_misc.string() << "\"" << std::endl;
	gi << "\t\t\tgame\t\t\t\t\"" << tf_sound_vo_english.string() << "\"" << std::endl;
	gi << "\t\t\tgame\t\t\t\t\"" << tf_textures.string() << "\"" << std::endl;
	gi << "\t\t\tgame\t\t\t\t\"" << tf.string() << "\"" << std::endl;

	gi << "\t\t\t" << std::endl;

	gi << "\t\t\tgame\t\t\t\t\"" << hl2_textures.string() << "\"" << std::endl;
	gi << "\t\t\tgame\t\t\t\t\"" << hl2_sound_vo_english.string() << "\"" << std::endl;
	gi << "\t\t\tgame\t\t\t\t\"" << hl2_sound_misc.string() << "\"" << std::endl;

	gi << giBot;

	gi.close();
}