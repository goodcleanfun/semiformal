#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scanner.h"


uint16_t scan_token(scanner_t *s)
{
    s->start = s->cursor;
    unsigned char *marker = s->cursor;

#define YYCTYPE     unsigned char
#define YYCURSOR    s->cursor
#define YYMARKER    marker
#define YYLIMIT     (s->end)
/*!re2c
re2c:yyfill:enable = 0;
!include "word_breaks/unicode_word_breaks.re";
!include "emoji_sequences/emoji_sequences.re";

// Start rules

any = [^\u0000];
newline = ("\r\n")|[\r\n\u2028\u2029\u000B\u000C\u0085];

ascii_letter = [A-Za-z];
digit = [0-9];

control_chars = [\x00-\x1f\x7f-\x9f];
other_format_chars = [\xad\u0600-\u0605\u061c\u06dd\u070f\u180e\u200b-\u200f\u202a-\u202e\u2060-\u2064\u2066-\u206f\ufeff\ufff9-\ufffb\U000110bd\U0001bca0-\U0001bca3\U0001d173-\U0001d17a\U000e0001\U000e0020-\U000e007f];
other_private_use_chars = [\ue000\uf8ff\U000f0000\U000ffffd\U00100000\U0010fffd];
other_surrogate_chars = [\ud800\udb7f-\udb80\udbff-\udc00\udfff];

letter_lower_chars = [a-z\xb5\xdf-\xf6\xf8-\xff\u0101\u0103\u0105\u0107\u0109\u010b\u010d\u010f\u0111\u0113\u0115\u0117\u0119\u011b\u011d\u011f\u0121\u0123\u0125\u0127\u0129\u012b\u012d\u012f\u0131\u0133\u0135\u0137-\u0138\u013a\u013c\u013e\u0140\u0142\u0144\u0146\u0148-\u0149\u014b\u014d\u014f\u0151\u0153\u0155\u0157\u0159\u015b\u015d\u015f\u0161\u0163\u0165\u0167\u0169\u016b\u016d\u016f\u0171\u0173\u0175\u0177\u017a\u017c\u017e-\u0180\u0183\u0185\u0188\u018c-\u018d\u0192\u0195\u0199-\u019b\u019e\u01a1\u01a3\u01a5\u01a8\u01aa-\u01ab\u01ad\u01b0\u01b4\u01b6\u01b9-\u01ba\u01bd-\u01bf\u01c6\u01c9\u01cc\u01ce\u01d0\u01d2\u01d4\u01d6\u01d8\u01da\u01dc-\u01dd\u01df\u01e1\u01e3\u01e5\u01e7\u01e9\u01eb\u01ed\u01ef-\u01f0\u01f3\u01f5\u01f9\u01fb\u01fd\u01ff\u0201\u0203\u0205\u0207\u0209\u020b\u020d\u020f\u0211\u0213\u0215\u0217\u0219\u021b\u021d\u021f\u0221\u0223\u0225\u0227\u0229\u022b\u022d\u022f\u0231\u0233-\u0239\u023c\u023f-\u0240\u0242\u0247\u0249\u024b\u024d\u024f-\u0293\u0295-\u02af\u0371\u0373\u0377\u037b-\u037d\u0390\u03ac-\u03ce\u03d0-\u03d1\u03d5-\u03d7\u03d9\u03db\u03dd\u03df\u03e1\u03e3\u03e5\u03e7\u03e9\u03eb\u03ed\u03ef-\u03f3\u03f5\u03f8\u03fb-\u03fc\u0430-\u045f\u0461\u0463\u0465\u0467\u0469\u046b\u046d\u046f\u0471\u0473\u0475\u0477\u0479\u047b\u047d\u047f\u0481\u048b\u048d\u048f\u0491\u0493\u0495\u0497\u0499\u049b\u049d\u049f\u04a1\u04a3\u04a5\u04a7\u04a9\u04ab\u04ad\u04af\u04b1\u04b3\u04b5\u04b7\u04b9\u04bb\u04bd\u04bf\u04c2\u04c4\u04c6\u04c8\u04ca\u04cc\u04ce-\u04cf\u04d1\u04d3\u04d5\u04d7\u04d9\u04db\u04dd\u04df\u04e1\u04e3\u04e5\u04e7\u04e9\u04eb\u04ed\u04ef\u04f1\u04f3\u04f5\u04f7\u04f9\u04fb\u04fd\u04ff\u0501\u0503\u0505\u0507\u0509\u050b\u050d\u050f\u0511\u0513\u0515\u0517\u0519\u051b\u051d\u051f\u0521\u0523\u0525\u0527\u0529\u052b\u052d\u052f\u0561-\u0587\u13f8-\u13fd\u1d00-\u1d2b\u1d6b-\u1d77\u1d79-\u1d9a\u1e01\u1e03\u1e05\u1e07\u1e09\u1e0b\u1e0d\u1e0f\u1e11\u1e13\u1e15\u1e17\u1e19\u1e1b\u1e1d\u1e1f\u1e21\u1e23\u1e25\u1e27\u1e29\u1e2b\u1e2d\u1e2f\u1e31\u1e33\u1e35\u1e37\u1e39\u1e3b\u1e3d\u1e3f\u1e41\u1e43\u1e45\u1e47\u1e49\u1e4b\u1e4d\u1e4f\u1e51\u1e53\u1e55\u1e57\u1e59\u1e5b\u1e5d\u1e5f\u1e61\u1e63\u1e65\u1e67\u1e69\u1e6b\u1e6d\u1e6f\u1e71\u1e73\u1e75\u1e77\u1e79\u1e7b\u1e7d\u1e7f\u1e81\u1e83\u1e85\u1e87\u1e89\u1e8b\u1e8d\u1e8f\u1e91\u1e93\u1e95-\u1e9d\u1e9f\u1ea1\u1ea3\u1ea5\u1ea7\u1ea9\u1eab\u1ead\u1eaf\u1eb1\u1eb3\u1eb5\u1eb7\u1eb9\u1ebb\u1ebd\u1ebf\u1ec1\u1ec3\u1ec5\u1ec7\u1ec9\u1ecb\u1ecd\u1ecf\u1ed1\u1ed3\u1ed5\u1ed7\u1ed9\u1edb\u1edd\u1edf\u1ee1\u1ee3\u1ee5\u1ee7\u1ee9\u1eeb\u1eed\u1eef\u1ef1\u1ef3\u1ef5\u1ef7\u1ef9\u1efb\u1efd\u1eff-\u1f07\u1f10-\u1f15\u1f20-\u1f27\u1f30-\u1f37\u1f40-\u1f45\u1f50-\u1f57\u1f60-\u1f67\u1f70-\u1f7d\u1f80-\u1f87\u1f90-\u1f97\u1fa0-\u1fa7\u1fb0-\u1fb4\u1fb6-\u1fb7\u1fbe\u1fc2-\u1fc4\u1fc6-\u1fc7\u1fd0-\u1fd3\u1fd6-\u1fd7\u1fe0-\u1fe7\u1ff2-\u1ff4\u1ff6-\u1ff7\u210a\u210e-\u210f\u2113\u212f\u2134\u2139\u213c-\u213d\u2146-\u2149\u214e\u2184\u2c30-\u2c5e\u2c61\u2c65-\u2c66\u2c68\u2c6a\u2c6c\u2c71\u2c73-\u2c74\u2c76-\u2c7b\u2c81\u2c83\u2c85\u2c87\u2c89\u2c8b\u2c8d\u2c8f\u2c91\u2c93\u2c95\u2c97\u2c99\u2c9b\u2c9d\u2c9f\u2ca1\u2ca3\u2ca5\u2ca7\u2ca9\u2cab\u2cad\u2caf\u2cb1\u2cb3\u2cb5\u2cb7\u2cb9\u2cbb\u2cbd\u2cbf\u2cc1\u2cc3\u2cc5\u2cc7\u2cc9\u2ccb\u2ccd\u2ccf\u2cd1\u2cd3\u2cd5\u2cd7\u2cd9\u2cdb\u2cdd\u2cdf\u2ce1\u2ce3-\u2ce4\u2cec\u2cee\u2cf3\u2d00-\u2d25\u2d27\u2d2d\ua641\ua643\ua645\ua647\ua649\ua64b\ua64d\ua64f\ua651\ua653\ua655\ua657\ua659\ua65b\ua65d\ua65f\ua661\ua663\ua665\ua667\ua669\ua66b\ua66d\ua681\ua683\ua685\ua687\ua689\ua68b\ua68d\ua68f\ua691\ua693\ua695\ua697\ua699\ua69b\ua723\ua725\ua727\ua729\ua72b\ua72d\ua72f-\ua731\ua733\ua735\ua737\ua739\ua73b\ua73d\ua73f\ua741\ua743\ua745\ua747\ua749\ua74b\ua74d\ua74f\ua751\ua753\ua755\ua757\ua759\ua75b\ua75d\ua75f\ua761\ua763\ua765\ua767\ua769\ua76b\ua76d\ua76f\ua771-\ua778\ua77a\ua77c\ua77f\ua781\ua783\ua785\ua787\ua78c\ua78e\ua791\ua793-\ua795\ua797\ua799\ua79b\ua79d\ua79f\ua7a1\ua7a3\ua7a5\ua7a7\ua7a9\ua7b5\ua7b7\ua7fa\uab30-\uab5a\uab60-\uab65\uab70-\uabbf\ufb00-\ufb06\ufb13-\ufb17\uff41-\uff5a\U00010428-\U0001044f\U00010cc0-\U00010cf2\U000118c0-\U000118df\U0001d41a-\U0001d433\U0001d44e-\U0001d454\U0001d456-\U0001d467\U0001d482-\U0001d49b\U0001d4b6-\U0001d4b9\U0001d4bb\U0001d4bd-\U0001d4c3\U0001d4c5-\U0001d4cf\U0001d4ea-\U0001d503\U0001d51e-\U0001d537\U0001d552-\U0001d56b\U0001d586-\U0001d59f\U0001d5ba-\U0001d5d3\U0001d5ee-\U0001d607\U0001d622-\U0001d63b\U0001d656-\U0001d66f\U0001d68a-\U0001d6a5\U0001d6c2-\U0001d6da\U0001d6dc-\U0001d6e1\U0001d6fc-\U0001d714\U0001d716-\U0001d71b\U0001d736-\U0001d74e\U0001d750-\U0001d755\U0001d770-\U0001d788\U0001d78a-\U0001d78f\U0001d7aa-\U0001d7c2\U0001d7c4-\U0001d7c9\U0001d7cb];
letter_modifier_chars = [\u02b0-\u02c1\u02c6-\u02d1\u02e0-\u02e4\u02ec\u02ee\u0374\u037a\u0559\u0640\u06e5-\u06e6\u07f4-\u07f5\u07fa\u081a\u0824\u0828\u0971\u0e46\u0ec6\u10fc\u17d7\u1843\u1aa7\u1c78-\u1c7d\u1d2c-\u1d6a\u1d78\u1d9b-\u1dbf\u2071\u207f\u2090-\u209c\u2c7c-\u2c7d\u2d6f\u2e2f\u3005\u3031-\u3035\u303b\u309d-\u309e\u30fc-\u30fe\ua015\ua4f8-\ua4fd\ua60c\ua67f\ua69c-\ua69d\ua717-\ua71f\ua770\ua788\ua7f8-\ua7f9\ua9cf\ua9e6\uaa70\uaadd\uaaf3-\uaaf4\uab5c-\uab5f\uff70\uff9e-\uff9f\U00016b40-\U00016b43\U00016f93-\U00016f9f];
letter_other_chars = [\xaa\xba\u01bb\u01c0-\u01c3\u0294\u05d0-\u05ea\u05f0-\u05f2\u0620-\u063f\u0641-\u064a\u066e-\u066f\u0671-\u06d3\u06d5\u06ee-\u06ef\u06fa-\u06fc\u06ff\u0710\u0712-\u072f\u074d-\u07a5\u07b1\u07ca-\u07ea\u0800-\u0815\u0840-\u0858\u08a0-\u08b4\u0904-\u0939\u093d\u0950\u0958-\u0961\u0972-\u0980\u0985-\u098c\u098f-\u0990\u0993-\u09a8\u09aa-\u09b0\u09b2\u09b6-\u09b9\u09bd\u09ce\u09dc-\u09dd\u09df-\u09e1\u09f0-\u09f1\u0a05-\u0a0a\u0a0f-\u0a10\u0a13-\u0a28\u0a2a-\u0a30\u0a32-\u0a33\u0a35-\u0a36\u0a38-\u0a39\u0a59-\u0a5c\u0a5e\u0a72-\u0a74\u0a85-\u0a8d\u0a8f-\u0a91\u0a93-\u0aa8\u0aaa-\u0ab0\u0ab2-\u0ab3\u0ab5-\u0ab9\u0abd\u0ad0\u0ae0-\u0ae1\u0af9\u0b05-\u0b0c\u0b0f-\u0b10\u0b13-\u0b28\u0b2a-\u0b30\u0b32-\u0b33\u0b35-\u0b39\u0b3d\u0b5c-\u0b5d\u0b5f-\u0b61\u0b71\u0b83\u0b85-\u0b8a\u0b8e-\u0b90\u0b92-\u0b95\u0b99-\u0b9a\u0b9c\u0b9e-\u0b9f\u0ba3-\u0ba4\u0ba8-\u0baa\u0bae-\u0bb9\u0bd0\u0c05-\u0c0c\u0c0e-\u0c10\u0c12-\u0c28\u0c2a-\u0c39\u0c3d\u0c58-\u0c5a\u0c60-\u0c61\u0c85-\u0c8c\u0c8e-\u0c90\u0c92-\u0ca8\u0caa-\u0cb3\u0cb5-\u0cb9\u0cbd\u0cde\u0ce0-\u0ce1\u0cf1-\u0cf2\u0d05-\u0d0c\u0d0e-\u0d10\u0d12-\u0d3a\u0d3d\u0d4e\u0d5f-\u0d61\u0d7a-\u0d7f\u0d85-\u0d96\u0d9a-\u0db1\u0db3-\u0dbb\u0dbd\u0dc0-\u0dc6\u0e01-\u0e30\u0e32-\u0e33\u0e40-\u0e45\u0e81-\u0e82\u0e84\u0e87-\u0e88\u0e8a\u0e8d\u0e94-\u0e97\u0e99-\u0e9f\u0ea1-\u0ea3\u0ea5\u0ea7\u0eaa-\u0eab\u0ead-\u0eb0\u0eb2-\u0eb3\u0ebd\u0ec0-\u0ec4\u0edc-\u0edf\u0f00\u0f40-\u0f47\u0f49-\u0f6c\u0f88-\u0f8c\u1000-\u102a\u103f\u1050-\u1055\u105a-\u105d\u1061\u1065-\u1066\u106e-\u1070\u1075-\u1081\u108e\u10d0-\u10fa\u10fd-\u1248\u124a-\u124d\u1250-\u1256\u1258\u125a-\u125d\u1260-\u1288\u128a-\u128d\u1290-\u12b0\u12b2-\u12b5\u12b8-\u12be\u12c0\u12c2-\u12c5\u12c8-\u12d6\u12d8-\u1310\u1312-\u1315\u1318-\u135a\u1380-\u138f\u1401-\u166c\u166f-\u167f\u1681-\u169a\u16a0-\u16ea\u16f1-\u16f8\u1700-\u170c\u170e-\u1711\u1720-\u1731\u1740-\u1751\u1760-\u176c\u176e-\u1770\u1780-\u17b3\u17dc\u1820-\u1842\u1844-\u1877\u1880-\u18a8\u18aa\u18b0-\u18f5\u1900-\u191e\u1950-\u196d\u1970-\u1974\u1980-\u19ab\u19b0-\u19c9\u1a00-\u1a16\u1a20-\u1a54\u1b05-\u1b33\u1b45-\u1b4b\u1b83-\u1ba0\u1bae-\u1baf\u1bba-\u1be5\u1c00-\u1c23\u1c4d-\u1c4f\u1c5a-\u1c77\u1ce9-\u1cec\u1cee-\u1cf1\u1cf5-\u1cf6\u2135-\u2138\u2d30-\u2d67\u2d80-\u2d96\u2da0-\u2da6\u2da8-\u2dae\u2db0-\u2db6\u2db8-\u2dbe\u2dc0-\u2dc6\u2dc8-\u2dce\u2dd0-\u2dd6\u2dd8-\u2dde\u3006\u303c\u3041-\u3096\u309f\u30a1-\u30fa\u30ff\u3105-\u312d\u3131-\u318e\u31a0-\u31ba\u31f0-\u31ff\u3400\u4db5\u4e00\u9fd5\ua000-\ua014\ua016-\ua48c\ua4d0-\ua4f7\ua500-\ua60b\ua610-\ua61f\ua62a-\ua62b\ua66e\ua6a0-\ua6e5\ua78f\ua7f7\ua7fb-\ua801\ua803-\ua805\ua807-\ua80a\ua80c-\ua822\ua840-\ua873\ua882-\ua8b3\ua8f2-\ua8f7\ua8fb\ua8fd\ua90a-\ua925\ua930-\ua946\ua960-\ua97c\ua984-\ua9b2\ua9e0-\ua9e4\ua9e7-\ua9ef\ua9fa-\ua9fe\uaa00-\uaa28\uaa40-\uaa42\uaa44-\uaa4b\uaa60-\uaa6f\uaa71-\uaa76\uaa7a\uaa7e-\uaaaf\uaab1\uaab5-\uaab6\uaab9-\uaabd\uaac0\uaac2\uaadb-\uaadc\uaae0-\uaaea\uaaf2\uab01-\uab06\uab09-\uab0e\uab11-\uab16\uab20-\uab26\uab28-\uab2e\uabc0-\uabe2\uac00\ud7a3\ud7b0-\ud7c6\ud7cb-\ud7fb\uf900-\ufa6d\ufa70-\ufad9\ufb1d\ufb1f-\ufb28\ufb2a-\ufb36\ufb38-\ufb3c\ufb3e\ufb40-\ufb41\ufb43-\ufb44\ufb46-\ufbb1\ufbd3-\ufd3d\ufd50-\ufd8f\ufd92-\ufdc7\ufdf0-\ufdfb\ufe70-\ufe74\ufe76-\ufefc\uff66-\uff6f\uff71-\uff9d\uffa0-\uffbe\uffc2-\uffc7\uffca-\uffcf\uffd2-\uffd7\uffda-\uffdc\U00010000-\U0001000b\U0001000d-\U00010026\U00010028-\U0001003a\U0001003c-\U0001003d\U0001003f-\U0001004d\U00010050-\U0001005d\U00010080-\U000100fa\U00010280-\U0001029c\U000102a0-\U000102d0\U00010300-\U0001031f\U00010330-\U00010340\U00010342-\U00010349\U00010350-\U00010375\U00010380-\U0001039d\U000103a0-\U000103c3\U000103c8-\U000103cf\U00010450-\U0001049d\U00010500-\U00010527\U00010530-\U00010563\U00010600-\U00010736\U00010740-\U00010755\U00010760-\U00010767\U00010800-\U00010805\U00010808\U0001080a-\U00010835\U00010837-\U00010838\U0001083c\U0001083f-\U00010855\U00010860-\U00010876\U00010880-\U0001089e\U000108e0-\U000108f2\U000108f4-\U000108f5\U00010900-\U00010915\U00010920-\U00010939\U00010980-\U000109b7\U000109be-\U000109bf\U00010a00\U00010a10-\U00010a13\U00010a15-\U00010a17\U00010a19-\U00010a33\U00010a60-\U00010a7c\U00010a80-\U00010a9c\U00010ac0-\U00010ac7\U00010ac9-\U00010ae4\U00010b00-\U00010b35\U00010b40-\U00010b55\U00010b60-\U00010b72\U00010b80-\U00010b91\U00010c00-\U00010c48\U00011003-\U00011037\U00011083-\U000110af\U000110d0-\U000110e8\U00011103-\U00011126\U00011150-\U00011172\U00011176\U00011183-\U000111b2\U000111c1-\U000111c4\U000111da\U000111dc\U00011200-\U00011211\U00011213-\U0001122b\U00011280-\U00011286\U00011288\U0001128a-\U0001128d\U0001128f-\U0001129d\U0001129f-\U000112a8\U000112b0-\U000112de\U00011305-\U0001130c\U0001130f-\U00011310\U00011313-\U00011328\U0001132a-\U00011330\U00011332-\U00011333\U00011335-\U00011339\U0001133d\U00011350\U0001135d-\U00011361\U00011480-\U000114af\U000114c4-\U000114c5\U000114c7\U00011580-\U000115ae\U000115d8-\U000115db\U00011600-\U0001162f\U00011644\U00011680-\U000116aa\U00011700-\U00011719\U000118ff\U00011ac0-\U00011af8\U00012000-\U00012399\U00012480-\U00012543\U00013000-\U0001342e\U00014400-\U00014646\U00016800-\U00016a38\U00016a40-\U00016a5e\U00016ad0-\U00016aed\U00016b00-\U00016b2f\U00016b63-\U00016b77\U00016b7d-\U00016b8f\U00016f00-\U00016f44\U00016f50\U0001b000-\U0001b001\U0001bc00-\U0001bc6a\U0001bc70-\U0001bc7c\U0001bc80-\U0001bc88\U0001bc90-\U0001bc99\U0001e800-\U0001e8c4\U0001ee00-\U0001ee03\U0001ee05-\U0001ee1f\U0001ee21-\U0001ee22\U0001ee24\U0001ee27\U0001ee29-\U0001ee32\U0001ee34-\U0001ee37\U0001ee39\U0001ee3b\U0001ee42\U0001ee47\U0001ee49\U0001ee4b\U0001ee4d-\U0001ee4f\U0001ee51-\U0001ee52\U0001ee54\U0001ee57\U0001ee59\U0001ee5b\U0001ee5d\U0001ee5f\U0001ee61-\U0001ee62\U0001ee64\U0001ee67-\U0001ee6a\U0001ee6c-\U0001ee72\U0001ee74-\U0001ee77\U0001ee79-\U0001ee7c\U0001ee7e\U0001ee80-\U0001ee89\U0001ee8b-\U0001ee9b\U0001eea1-\U0001eea3\U0001eea5-\U0001eea9\U0001eeab-\U0001eebb\U00020000\U0002a6d6\U0002a700\U0002b734\U0002b740\U0002b81d\U0002b820\U0002cea1\U0002f800-\U0002fa1d];
letter_title_chars = [\u01c5\u01c8\u01cb\u01f2\u1f88-\u1f8f\u1f98-\u1f9f\u1fa8-\u1faf\u1fbc\u1fcc\u1ffc];
letter_upper_chars = [A-Z\xc0-\xd6\xd8-\xde\u0100\u0102\u0104\u0106\u0108\u010a\u010c\u010e\u0110\u0112\u0114\u0116\u0118\u011a\u011c\u011e\u0120\u0122\u0124\u0126\u0128\u012a\u012c\u012e\u0130\u0132\u0134\u0136\u0139\u013b\u013d\u013f\u0141\u0143\u0145\u0147\u014a\u014c\u014e\u0150\u0152\u0154\u0156\u0158\u015a\u015c\u015e\u0160\u0162\u0164\u0166\u0168\u016a\u016c\u016e\u0170\u0172\u0174\u0176\u0178-\u0179\u017b\u017d\u0181-\u0182\u0184\u0186-\u0187\u0189-\u018b\u018e-\u0191\u0193-\u0194\u0196-\u0198\u019c-\u019d\u019f-\u01a0\u01a2\u01a4\u01a6-\u01a7\u01a9\u01ac\u01ae-\u01af\u01b1-\u01b3\u01b5\u01b7-\u01b8\u01bc\u01c4\u01c7\u01ca\u01cd\u01cf\u01d1\u01d3\u01d5\u01d7\u01d9\u01db\u01de\u01e0\u01e2\u01e4\u01e6\u01e8\u01ea\u01ec\u01ee\u01f1\u01f4\u01f6-\u01f8\u01fa\u01fc\u01fe\u0200\u0202\u0204\u0206\u0208\u020a\u020c\u020e\u0210\u0212\u0214\u0216\u0218\u021a\u021c\u021e\u0220\u0222\u0224\u0226\u0228\u022a\u022c\u022e\u0230\u0232\u023a-\u023b\u023d-\u023e\u0241\u0243-\u0246\u0248\u024a\u024c\u024e\u0370\u0372\u0376\u037f\u0386\u0388-\u038a\u038c\u038e-\u038f\u0391-\u03a1\u03a3-\u03ab\u03cf\u03d2-\u03d4\u03d8\u03da\u03dc\u03de\u03e0\u03e2\u03e4\u03e6\u03e8\u03ea\u03ec\u03ee\u03f4\u03f7\u03f9-\u03fa\u03fd-\u042f\u0460\u0462\u0464\u0466\u0468\u046a\u046c\u046e\u0470\u0472\u0474\u0476\u0478\u047a\u047c\u047e\u0480\u048a\u048c\u048e\u0490\u0492\u0494\u0496\u0498\u049a\u049c\u049e\u04a0\u04a2\u04a4\u04a6\u04a8\u04aa\u04ac\u04ae\u04b0\u04b2\u04b4\u04b6\u04b8\u04ba\u04bc\u04be\u04c0-\u04c1\u04c3\u04c5\u04c7\u04c9\u04cb\u04cd\u04d0\u04d2\u04d4\u04d6\u04d8\u04da\u04dc\u04de\u04e0\u04e2\u04e4\u04e6\u04e8\u04ea\u04ec\u04ee\u04f0\u04f2\u04f4\u04f6\u04f8\u04fa\u04fc\u04fe\u0500\u0502\u0504\u0506\u0508\u050a\u050c\u050e\u0510\u0512\u0514\u0516\u0518\u051a\u051c\u051e\u0520\u0522\u0524\u0526\u0528\u052a\u052c\u052e\u0531-\u0556\u10a0-\u10c5\u10c7\u10cd\u13a0-\u13f5\u1e00\u1e02\u1e04\u1e06\u1e08\u1e0a\u1e0c\u1e0e\u1e10\u1e12\u1e14\u1e16\u1e18\u1e1a\u1e1c\u1e1e\u1e20\u1e22\u1e24\u1e26\u1e28\u1e2a\u1e2c\u1e2e\u1e30\u1e32\u1e34\u1e36\u1e38\u1e3a\u1e3c\u1e3e\u1e40\u1e42\u1e44\u1e46\u1e48\u1e4a\u1e4c\u1e4e\u1e50\u1e52\u1e54\u1e56\u1e58\u1e5a\u1e5c\u1e5e\u1e60\u1e62\u1e64\u1e66\u1e68\u1e6a\u1e6c\u1e6e\u1e70\u1e72\u1e74\u1e76\u1e78\u1e7a\u1e7c\u1e7e\u1e80\u1e82\u1e84\u1e86\u1e88\u1e8a\u1e8c\u1e8e\u1e90\u1e92\u1e94\u1e9e\u1ea0\u1ea2\u1ea4\u1ea6\u1ea8\u1eaa\u1eac\u1eae\u1eb0\u1eb2\u1eb4\u1eb6\u1eb8\u1eba\u1ebc\u1ebe\u1ec0\u1ec2\u1ec4\u1ec6\u1ec8\u1eca\u1ecc\u1ece\u1ed0\u1ed2\u1ed4\u1ed6\u1ed8\u1eda\u1edc\u1ede\u1ee0\u1ee2\u1ee4\u1ee6\u1ee8\u1eea\u1eec\u1eee\u1ef0\u1ef2\u1ef4\u1ef6\u1ef8\u1efa\u1efc\u1efe\u1f08-\u1f0f\u1f18-\u1f1d\u1f28-\u1f2f\u1f38-\u1f3f\u1f48-\u1f4d\u1f59\u1f5b\u1f5d\u1f5f\u1f68-\u1f6f\u1fb8-\u1fbb\u1fc8-\u1fcb\u1fd8-\u1fdb\u1fe8-\u1fec\u1ff8-\u1ffb\u2102\u2107\u210b-\u210d\u2110-\u2112\u2115\u2119-\u211d\u2124\u2126\u2128\u212a-\u212d\u2130-\u2133\u213e-\u213f\u2145\u2183\u2c00-\u2c2e\u2c60\u2c62-\u2c64\u2c67\u2c69\u2c6b\u2c6d-\u2c70\u2c72\u2c75\u2c7e-\u2c80\u2c82\u2c84\u2c86\u2c88\u2c8a\u2c8c\u2c8e\u2c90\u2c92\u2c94\u2c96\u2c98\u2c9a\u2c9c\u2c9e\u2ca0\u2ca2\u2ca4\u2ca6\u2ca8\u2caa\u2cac\u2cae\u2cb0\u2cb2\u2cb4\u2cb6\u2cb8\u2cba\u2cbc\u2cbe\u2cc0\u2cc2\u2cc4\u2cc6\u2cc8\u2cca\u2ccc\u2cce\u2cd0\u2cd2\u2cd4\u2cd6\u2cd8\u2cda\u2cdc\u2cde\u2ce0\u2ce2\u2ceb\u2ced\u2cf2\ua640\ua642\ua644\ua646\ua648\ua64a\ua64c\ua64e\ua650\ua652\ua654\ua656\ua658\ua65a\ua65c\ua65e\ua660\ua662\ua664\ua666\ua668\ua66a\ua66c\ua680\ua682\ua684\ua686\ua688\ua68a\ua68c\ua68e\ua690\ua692\ua694\ua696\ua698\ua69a\ua722\ua724\ua726\ua728\ua72a\ua72c\ua72e\ua732\ua734\ua736\ua738\ua73a\ua73c\ua73e\ua740\ua742\ua744\ua746\ua748\ua74a\ua74c\ua74e\ua750\ua752\ua754\ua756\ua758\ua75a\ua75c\ua75e\ua760\ua762\ua764\ua766\ua768\ua76a\ua76c\ua76e\ua779\ua77b\ua77d-\ua77e\ua780\ua782\ua784\ua786\ua78b\ua78d\ua790\ua792\ua796\ua798\ua79a\ua79c\ua79e\ua7a0\ua7a2\ua7a4\ua7a6\ua7a8\ua7aa-\ua7ad\ua7b0-\ua7b4\ua7b6\uff21-\uff3a\U00010400-\U00010427\U00010c80-\U00010cb2\U000118a0-\U000118bf\U0001d400-\U0001d419\U0001d434-\U0001d44d\U0001d468-\U0001d481\U0001d49c\U0001d49e-\U0001d49f\U0001d4a2\U0001d4a5-\U0001d4a6\U0001d4a9-\U0001d4ac\U0001d4ae-\U0001d4b5\U0001d4d0-\U0001d4e9\U0001d504-\U0001d505\U0001d507-\U0001d50a\U0001d50d-\U0001d514\U0001d516-\U0001d51c\U0001d538-\U0001d539\U0001d53b-\U0001d53e\U0001d540-\U0001d544\U0001d546\U0001d54a-\U0001d550\U0001d56c-\U0001d585\U0001d5a0-\U0001d5b9\U0001d5d4-\U0001d5ed\U0001d608-\U0001d621\U0001d63c-\U0001d655\U0001d670-\U0001d689\U0001d6a8-\U0001d6c0\U0001d6e2-\U0001d6fa\U0001d71c-\U0001d734\U0001d756-\U0001d76e\U0001d790-\U0001d7a8\U0001d7ca];

mark_spacing_combining_chars = [\u0903\u093b\u093e-\u0940\u0949-\u094c\u094e-\u094f\u0982-\u0983\u09be-\u09c0\u09c7-\u09c8\u09cb-\u09cc\u09d7\u0a03\u0a3e-\u0a40\u0a83\u0abe-\u0ac0\u0ac9\u0acb-\u0acc\u0b02-\u0b03\u0b3e\u0b40\u0b47-\u0b48\u0b4b-\u0b4c\u0b57\u0bbe-\u0bbf\u0bc1-\u0bc2\u0bc6-\u0bc8\u0bca-\u0bcc\u0bd7\u0c01-\u0c03\u0c41-\u0c44\u0c82-\u0c83\u0cbe\u0cc0-\u0cc4\u0cc7-\u0cc8\u0cca-\u0ccb\u0cd5-\u0cd6\u0d02-\u0d03\u0d3e-\u0d40\u0d46-\u0d48\u0d4a-\u0d4c\u0d57\u0d82-\u0d83\u0dcf-\u0dd1\u0dd8-\u0ddf\u0df2-\u0df3\u0f3e-\u0f3f\u0f7f\u102b-\u102c\u1031\u1038\u103b-\u103c\u1056-\u1057\u1062-\u1064\u1067-\u106d\u1083-\u1084\u1087-\u108c\u108f\u109a-\u109c\u17b6\u17be-\u17c5\u17c7-\u17c8\u1923-\u1926\u1929-\u192b\u1930-\u1931\u1933-\u1938\u1a19-\u1a1a\u1a55\u1a57\u1a61\u1a63-\u1a64\u1a6d-\u1a72\u1b04\u1b35\u1b3b\u1b3d-\u1b41\u1b43-\u1b44\u1b82\u1ba1\u1ba6-\u1ba7\u1baa\u1be7\u1bea-\u1bec\u1bee\u1bf2-\u1bf3\u1c24-\u1c2b\u1c34-\u1c35\u1ce1\u1cf2-\u1cf3\u302e-\u302f\ua823-\ua824\ua827\ua880-\ua881\ua8b4-\ua8c3\ua952-\ua953\ua983\ua9b4-\ua9b5\ua9ba-\ua9bb\ua9bd-\ua9c0\uaa2f-\uaa30\uaa33-\uaa34\uaa4d\uaa7b\uaa7d\uaaeb\uaaee-\uaaef\uaaf5\uabe3-\uabe4\uabe6-\uabe7\uabe9-\uabea\uabec\U00011000\U00011002\U00011082\U000110b0-\U000110b2\U000110b7-\U000110b8\U0001112c\U00011182\U000111b3-\U000111b5\U000111bf-\U000111c0\U0001122c-\U0001122e\U00011232-\U00011233\U00011235\U000112e0-\U000112e2\U00011302-\U00011303\U0001133e-\U0001133f\U00011341-\U00011344\U00011347-\U00011348\U0001134b-\U0001134d\U00011357\U00011362-\U00011363\U000114b0-\U000114b2\U000114b9\U000114bb-\U000114be\U000114c1\U000115af-\U000115b1\U000115b8-\U000115bb\U000115be\U00011630-\U00011632\U0001163b-\U0001163c\U0001163e\U000116ac\U000116ae-\U000116af\U000116b6\U00011720-\U00011721\U00011726\U00016f51-\U00016f7e\U0001d165-\U0001d166\U0001d16d-\U0001d172];
mark_enclosing_chars = [\u0488-\u0489\u1abe\u20dd-\u20e0\u20e2-\u20e4\ua670-\ua672];
mark_nonspacing_chars = [\u0300-\u036f\u0483-\u0487\u0591-\u05bd\u05bf\u05c1-\u05c2\u05c4-\u05c5\u05c7\u0610-\u061a\u064b-\u065f\u0670\u06d6-\u06dc\u06df-\u06e4\u06e7-\u06e8\u06ea-\u06ed\u0711\u0730-\u074a\u07a6-\u07b0\u07eb-\u07f3\u0816-\u0819\u081b-\u0823\u0825-\u0827\u0829-\u082d\u0859-\u085b\u08e3-\u0902\u093a\u093c\u0941-\u0948\u094d\u0951-\u0957\u0962-\u0963\u0981\u09bc\u09c1-\u09c4\u09cd\u09e2-\u09e3\u0a01-\u0a02\u0a3c\u0a41-\u0a42\u0a47-\u0a48\u0a4b-\u0a4d\u0a51\u0a70-\u0a71\u0a75\u0a81-\u0a82\u0abc\u0ac1-\u0ac5\u0ac7-\u0ac8\u0acd\u0ae2-\u0ae3\u0b01\u0b3c\u0b3f\u0b41-\u0b44\u0b4d\u0b56\u0b62-\u0b63\u0b82\u0bc0\u0bcd\u0c00\u0c3e-\u0c40\u0c46-\u0c48\u0c4a-\u0c4d\u0c55-\u0c56\u0c62-\u0c63\u0c81\u0cbc\u0cbf\u0cc6\u0ccc-\u0ccd\u0ce2-\u0ce3\u0d01\u0d41-\u0d44\u0d4d\u0d62-\u0d63\u0dca\u0dd2-\u0dd4\u0dd6\u0e31\u0e34-\u0e3a\u0e47-\u0e4e\u0eb1\u0eb4-\u0eb9\u0ebb-\u0ebc\u0ec8-\u0ecd\u0f18-\u0f19\u0f35\u0f37\u0f39\u0f71-\u0f7e\u0f80-\u0f84\u0f86-\u0f87\u0f8d-\u0f97\u0f99-\u0fbc\u0fc6\u102d-\u1030\u1032-\u1037\u1039-\u103a\u103d-\u103e\u1058-\u1059\u105e-\u1060\u1071-\u1074\u1082\u1085-\u1086\u108d\u109d\u135d-\u135f\u1712-\u1714\u1732-\u1734\u1752-\u1753\u1772-\u1773\u17b4-\u17b5\u17b7-\u17bd\u17c6\u17c9-\u17d3\u17dd\u180b-\u180d\u18a9\u1920-\u1922\u1927-\u1928\u1932\u1939-\u193b\u1a17-\u1a18\u1a1b\u1a56\u1a58-\u1a5e\u1a60\u1a62\u1a65-\u1a6c\u1a73-\u1a7c\u1a7f\u1ab0-\u1abd\u1b00-\u1b03\u1b34\u1b36-\u1b3a\u1b3c\u1b42\u1b6b-\u1b73\u1b80-\u1b81\u1ba2-\u1ba5\u1ba8-\u1ba9\u1bab-\u1bad\u1be6\u1be8-\u1be9\u1bed\u1bef-\u1bf1\u1c2c-\u1c33\u1c36-\u1c37\u1cd0-\u1cd2\u1cd4-\u1ce0\u1ce2-\u1ce8\u1ced\u1cf4\u1cf8-\u1cf9\u1dc0-\u1df5\u1dfc-\u1dff\u20d0-\u20dc\u20e1\u20e5-\u20f0\u2cef-\u2cf1\u2d7f\u2de0-\u2dff\u302a-\u302d\u3099-\u309a\ua66f\ua674-\ua67d\ua69e-\ua69f\ua6f0-\ua6f1\ua802\ua806\ua80b\ua825-\ua826\ua8c4\ua8e0-\ua8f1\ua926-\ua92d\ua947-\ua951\ua980-\ua982\ua9b3\ua9b6-\ua9b9\ua9bc\ua9e5\uaa29-\uaa2e\uaa31-\uaa32\uaa35-\uaa36\uaa43\uaa4c\uaa7c\uaab0\uaab2-\uaab4\uaab7-\uaab8\uaabe-\uaabf\uaac1\uaaec-\uaaed\uaaf6\uabe5\uabe8\uabed\ufb1e\ufe00-\ufe0f\ufe20-\ufe2f\U000101fd\U000102e0\U00010376-\U0001037a\U00010a01-\U00010a03\U00010a05-\U00010a06\U00010a0c-\U00010a0f\U00010a38-\U00010a3a\U00010a3f\U00010ae5-\U00010ae6\U00011001\U00011038-\U00011046\U0001107f-\U00011081\U000110b3-\U000110b6\U000110b9-\U000110ba\U00011100-\U00011102\U00011127-\U0001112b\U0001112d-\U00011134\U00011173\U00011180-\U00011181\U000111b6-\U000111be\U000111ca-\U000111cc\U0001122f-\U00011231\U00011234\U00011236-\U00011237\U000112df\U000112e3-\U000112ea\U00011300-\U00011301\U0001133c\U00011340\U00011366-\U0001136c\U00011370-\U00011374\U000114b3-\U000114b8\U000114ba\U000114bf-\U000114c0\U000114c2-\U000114c3\U000115b2-\U000115b5\U000115bc-\U000115bd\U000115bf-\U000115c0\U000115dc-\U000115dd\U00011633-\U0001163a\U0001163d\U0001163f-\U00011640\U000116ab\U000116ad\U000116b0-\U000116b5\U000116b7\U0001171d-\U0001171f\U00011722-\U00011725\U00011727-\U0001172b\U00016af0-\U00016af4\U00016b30-\U00016b36\U00016f8f-\U00016f92\U0001bc9d-\U0001bc9e\U0001d167-\U0001d169\U0001d17b-\U0001d182\U0001d185-\U0001d18b\U0001d1aa-\U0001d1ad\U0001d242-\U0001d244\U0001da00-\U0001da36\U0001da3b-\U0001da6c\U0001da75\U0001da84\U0001da9b-\U0001da9f\U0001daa1-\U0001daaf\U0001e8d0-\U0001e8d6\U000e0100-\U000e01ef];

number_or_digit_chars = [0-9\u0660-\u0669\u06f0-\u06f9\u07c0-\u07c9\u0966-\u096f\u09e6-\u09ef\u0a66-\u0a6f\u0ae6-\u0aef\u0b66-\u0b6f\u0be6-\u0bef\u0c66-\u0c6f\u0ce6-\u0cef\u0d66-\u0d6f\u0de6-\u0def\u0e50-\u0e59\u0ed0-\u0ed9\u0f20-\u0f29\u1040-\u1049\u1090-\u1099\u17e0-\u17e9\u1810-\u1819\u1946-\u194f\u19d0-\u19d9\u1a80-\u1a89\u1a90-\u1a99\u1b50-\u1b59\u1bb0-\u1bb9\u1c40-\u1c49\u1c50-\u1c59\ua620-\ua629\ua8d0-\ua8d9\ua900-\ua909\ua9d0-\ua9d9\ua9f0-\ua9f9\uaa50-\uaa59\uabf0-\uabf9\uff10-\uff19\U000104a0-\U000104a9\U00011066-\U0001106f\U000110f0-\U000110f9\U00011136-\U0001113f\U000111d0-\U000111d9\U000112f0-\U000112f9\U000114d0-\U000114d9\U00011650-\U00011659\U000116c0-\U000116c9\U00011730-\U00011739\U000118e0-\U000118e9\U00016a60-\U00016a69\U00016b50-\U00016b59\U0001d7ce-\U0001d7ff];
number_letter_chars = [\u16ee-\u16f0\u2160-\u2182\u2185-\u2188\u3007\u3021-\u3029\u3038-\u303a\ua6e6-\ua6ef\U00010140-\U00010174\U00010341\U0001034a\U000103d1-\U000103d5\U00012400-\U0001246e];
number_other_chars = [\xb2-\xb3\xb9\xbc-\xbe\u09f4-\u09f9\u0b72-\u0b77\u0bf0-\u0bf2\u0c78-\u0c7e\u0d70-\u0d75\u0f2a-\u0f33\u1369-\u137c\u17f0-\u17f9\u19da\u2070\u2074-\u2079\u2080-\u2089\u2150-\u215f\u2189\u2460-\u249b\u24ea-\u24ff\u2776-\u2793\u2cfd\u3192-\u3195\u3220-\u3229\u3248-\u324f\u3251-\u325f\u3280-\u3289\u32b1-\u32bf\ua830-\ua835\U00010107-\U00010133\U00010175-\U00010178\U0001018a-\U0001018b\U000102e1-\U000102fb\U00010320-\U00010323\U00010858-\U0001085f\U00010879-\U0001087f\U000108a7-\U000108af\U000108fb-\U000108ff\U00010916-\U0001091b\U000109bc-\U000109bd\U000109c0-\U000109cf\U000109d2-\U000109ff\U00010a40-\U00010a47\U00010a7d-\U00010a7e\U00010a9d-\U00010a9f\U00010aeb-\U00010aef\U00010b58-\U00010b5f\U00010b78-\U00010b7f\U00010ba9-\U00010baf\U00010cfa-\U00010cff\U00010e60-\U00010e7e\U00011052-\U00011065\U000111e1-\U000111f4\U0001173a-\U0001173b\U000118ea-\U000118f2\U00016b5b-\U00016b61\U0001d360-\U0001d371\U0001e8c7-\U0001e8cf\U0001f100-\U0001f10c];

punct_connector_chars = [_\u203f-\u2040\u2054\ufe33-\ufe34\ufe4d-\ufe4f\uff3f];
punct_dash_chars = [\-\u058a\u05be\u1400\u1806\u2010-\u2015\u2e17\u2e1a\u2e3a-\u2e3b\u2e40\u301c\u3030\u30a0\ufe31-\ufe32\ufe58\ufe63\uff0d];
punct_close_chars = [)\]\}\u0f3b\u0f3d\u169c\u2046\u207e\u208e\u2309\u230b\u232a\u2769\u276b\u276d\u276f\u2771\u2773\u2775\u27c6\u27e7\u27e9\u27eb\u27ed\u27ef\u2984\u2986\u2988\u298a\u298c\u298e\u2990\u2992\u2994\u2996\u2998\u29d9\u29db\u29fd\u2e23\u2e25\u2e27\u2e29\u3009\u300b\u300d\u300f\u3011\u3015\u3017\u3019\u301b\u301e-\u301f\ufd3e\ufe18\ufe36\ufe38\ufe3a\ufe3c\ufe3e\ufe40\ufe42\ufe44\ufe48\ufe5a\ufe5c\ufe5e\uff09\uff3d\uff5d\uff60\uff63];
punct_final_quote_chars = [\xbb\u2019\u201d\u203a\u2e03\u2e05\u2e0a\u2e0d\u2e1d\u2e21];
punct_initial_quote_chars = [\xab\u2018\u201b-\u201c\u201f\u2039\u2e02\u2e04\u2e09\u2e0c\u2e1c\u2e20];
punct_other_chars = [!-#%-'*,.-/:-;?-@\\\xa1\xa7\xb6-\xb7\xbf\u037e\u0387\u055a-\u055f\u0589\u05c0\u05c3\u05c6\u05f3-\u05f4\u0609-\u060a\u060c-\u060d\u061b\u061e-\u061f\u066a-\u066d\u06d4\u0700-\u070d\u07f7-\u07f9\u0830-\u083e\u085e\u0964-\u0965\u0970\u0af0\u0df4\u0e4f\u0e5a-\u0e5b\u0f04-\u0f12\u0f14\u0f85\u0fd0-\u0fd4\u0fd9-\u0fda\u104a-\u104f\u10fb\u1360-\u1368\u166d-\u166e\u16eb-\u16ed\u1735-\u1736\u17d4-\u17d6\u17d8-\u17da\u1800-\u1805\u1807-\u180a\u1944-\u1945\u1a1e-\u1a1f\u1aa0-\u1aa6\u1aa8-\u1aad\u1b5a-\u1b60\u1bfc-\u1bff\u1c3b-\u1c3f\u1c7e-\u1c7f\u1cc0-\u1cc7\u1cd3\u2016-\u2017\u2020-\u2027\u2030-\u2038\u203b-\u203e\u2041-\u2043\u2047-\u2051\u2053\u2055-\u205e\u2cf9-\u2cfc\u2cfe-\u2cff\u2d70\u2e00-\u2e01\u2e06-\u2e08\u2e0b\u2e0e-\u2e16\u2e18-\u2e19\u2e1b\u2e1e-\u2e1f\u2e2a-\u2e2e\u2e30-\u2e39\u2e3c-\u2e3f\u2e41\u3001-\u3003\u303d\u30fb\ua4fe-\ua4ff\ua60d-\ua60f\ua673\ua67e\ua6f2-\ua6f7\ua874-\ua877\ua8ce-\ua8cf\ua8f8-\ua8fa\ua8fc\ua92e-\ua92f\ua95f\ua9c1-\ua9cd\ua9de-\ua9df\uaa5c-\uaa5f\uaade-\uaadf\uaaf0-\uaaf1\uabeb\ufe10-\ufe16\ufe19\ufe30\ufe45-\ufe46\ufe49-\ufe4c\ufe50-\ufe52\ufe54-\ufe57\ufe5f-\ufe61\ufe68\ufe6a-\ufe6b\uff01-\uff03\uff05-\uff07\uff0a\uff0c\uff0e-\uff0f\uff1a-\uff1b\uff1f-\uff20\uff3c\uff61\uff64-\uff65\U00010100-\U00010102\U0001039f\U000103d0\U0001056f\U00010857\U0001091f\U0001093f\U00010a50-\U00010a58\U00010a7f\U00010af0-\U00010af6\U00010b39-\U00010b3f\U00010b99-\U00010b9c\U00011047-\U0001104d\U000110bb-\U000110bc\U000110be-\U000110c1\U00011140-\U00011143\U00011174-\U00011175\U000111c5-\U000111c9\U000111cd\U000111db\U000111dd-\U000111df\U00011238-\U0001123d\U000112a9\U000114c6\U000115c1-\U000115d7\U00011641-\U00011643\U0001173c-\U0001173e\U00012470-\U00012474\U00016a6e-\U00016a6f\U00016af5\U00016b37-\U00016b3b\U00016b44\U0001bc9f\U0001da87-\U0001da8b];
punct_open_chars = [(\[\{\u0f3a\u0f3c\u169b\u201a\u201e\u2045\u207d\u208d\u2308\u230a\u2329\u2768\u276a\u276c\u276e\u2770\u2772\u2774\u27c5\u27e6\u27e8\u27ea\u27ec\u27ee\u2983\u2985\u2987\u2989\u298b\u298d\u298f\u2991\u2993\u2995\u2997\u29d8\u29da\u29fc\u2e22\u2e24\u2e26\u2e28\u2e42\u3008\u300a\u300c\u300e\u3010\u3014\u3016\u3018\u301a\u301d\ufd3f\ufe17\ufe35\ufe37\ufe39\ufe3b\ufe3d\ufe3f\ufe41\ufe43\ufe47\ufe59\ufe5b\ufe5d\uff08\uff3b\uff5b\uff5f\uff62];

currency_symbol_chars = [$\xa2-\xa5\u058f\u060b\u09f2-\u09f3\u09fb\u0af1\u0bf9\u0e3f\u17db\u20a0-\u20be\ua838\ufdfc\ufe69\uff04\uffe0-\uffe1\uffe5-\uffe6];
symbol_modifier_chars = [\^`\xa8\xaf\xb4\xb8\u02c2-\u02c5\u02d2-\u02df\u02e5-\u02eb\u02ed\u02ef-\u02ff\u0375\u0384-\u0385\u1fbd\u1fbf-\u1fc1\u1fcd-\u1fcf\u1fdd-\u1fdf\u1fed-\u1fef\u1ffd-\u1ffe\u309b-\u309c\ua700-\ua716\ua720-\ua721\ua789-\ua78a\uab5b\ufbb2-\ufbc1\uff3e\uff40\uffe3\U0001f3fb-\U0001f3ff];
symbol_math_chars = [+<->|~\xac\xb1\xd7\xf7\u03f6\u0606-\u0608\u2044\u2052\u207a-\u207c\u208a-\u208c\u2118\u2140-\u2144\u214b\u2190-\u2194\u219a-\u219b\u21a0\u21a3\u21a6\u21ae\u21ce-\u21cf\u21d2\u21d4\u21f4-\u22ff\u2320-\u2321\u237c\u239b-\u23b3\u23dc-\u23e1\u25b7\u25c1\u25f8-\u25ff\u266f\u27c0-\u27c4\u27c7-\u27e5\u27f0-\u27ff\u2900-\u2982\u2999-\u29d7\u29dc-\u29fb\u29fe-\u2aff\u2b30-\u2b44\u2b47-\u2b4c\ufb29\ufe62\ufe64-\ufe66\uff0b\uff1c-\uff1e\uff5c\uff5e\uffe2\uffe9-\uffec\U0001d6c1\U0001d6db\U0001d6fb\U0001d715\U0001d735\U0001d74f\U0001d76f\U0001d789\U0001d7a9\U0001d7c3\U0001eef0-\U0001eef1];
symbol_other_chars = [\xa6\xa9\xae\xb0\u0482\u058d-\u058e\u060e-\u060f\u06de\u06e9\u06fd-\u06fe\u07f6\u09fa\u0b70\u0bf3-\u0bf8\u0bfa\u0c7f\u0d79\u0f01-\u0f03\u0f13\u0f15-\u0f17\u0f1a-\u0f1f\u0f34\u0f36\u0f38\u0fbe-\u0fc5\u0fc7-\u0fcc\u0fce-\u0fcf\u0fd5-\u0fd8\u109e-\u109f\u1390-\u1399\u1940\u19de-\u19ff\u1b61-\u1b6a\u1b74-\u1b7c\u2100-\u2101\u2103-\u2106\u2108-\u2109\u2114\u2116-\u2117\u211e-\u2123\u2125\u2127\u2129\u212e\u213a-\u213b\u214a\u214c-\u214d\u214f\u218a-\u218b\u2195-\u2199\u219c-\u219f\u21a1-\u21a2\u21a4-\u21a5\u21a7-\u21ad\u21af-\u21cd\u21d0-\u21d1\u21d3\u21d5-\u21f3\u2300-\u2307\u230c-\u231f\u2322-\u2328\u232b-\u237b\u237d-\u239a\u23b4-\u23db\u23e2-\u23fa\u2400-\u2426\u2440-\u244a\u249c-\u24e9\u2500-\u25b6\u25b8-\u25c0\u25c2-\u25f7\u2600-\u266e\u2670-\u2767\u2794-\u27bf\u2800-\u28ff\u2b00-\u2b2f\u2b45-\u2b46\u2b4d-\u2b73\u2b76-\u2b95\u2b98-\u2bb9\u2bbd-\u2bc8\u2bca-\u2bd1\u2bec-\u2bef\u2ce5-\u2cea\u2e80-\u2e99\u2e9b-\u2ef3\u2f00-\u2fd5\u2ff0-\u2ffb\u3004\u3012-\u3013\u3020\u3036-\u3037\u303e-\u303f\u3190-\u3191\u3196-\u319f\u31c0-\u31e3\u3200-\u321e\u322a-\u3247\u3250\u3260-\u327f\u328a-\u32b0\u32c0-\u32fe\u3300-\u33ff\u4dc0-\u4dff\ua490-\ua4c6\ua828-\ua82b\ua836-\ua837\ua839\uaa77-\uaa79\ufdfd\uffe4\uffe8\uffed-\uffee\ufffc-\ufffd\U00010137-\U0001013f\U00010179-\U00010189\U0001018c\U00010190-\U0001019b\U000101a0\U000101d0-\U000101fc\U00010877-\U00010878\U00010ac8\U0001173f\U00016b3c-\U00016b3f\U00016b45\U0001bc9c\U0001d000-\U0001d0f5\U0001d100-\U0001d126\U0001d129-\U0001d164\U0001d16a-\U0001d16c\U0001d183-\U0001d184\U0001d18c-\U0001d1a9\U0001d1ae-\U0001d1e8\U0001d200-\U0001d241\U0001d245\U0001d300-\U0001d356\U0001d800-\U0001d9ff\U0001da37-\U0001da3a\U0001da6d-\U0001da74\U0001da76-\U0001da83\U0001da85-\U0001da86\U0001f000-\U0001f02b\U0001f030-\U0001f093\U0001f0a0-\U0001f0ae\U0001f0b1-\U0001f0bf\U0001f0c1-\U0001f0cf\U0001f0d1-\U0001f0f5\U0001f110-\U0001f12e\U0001f130-\U0001f16b\U0001f170-\U0001f19a\U0001f1e6-\U0001f202\U0001f210-\U0001f23a\U0001f240-\U0001f248\U0001f250-\U0001f251\U0001f300-\U0001f3fa\U0001f400-\U0001f579\U0001f57b-\U0001f5a3\U0001f5a5-\U0001f6d0\U0001f6e0-\U0001f6ec\U0001f6f0-\U0001f6f3\U0001f700-\U0001f773\U0001f780-\U0001f7d4\U0001f800-\U0001f80b\U0001f810-\U0001f847\U0001f850-\U0001f859\U0001f860-\U0001f887\U0001f890-\U0001f8ad\U0001f910-\U0001f918\U0001f980-\U0001f984\U0001f9c0];

separator_line_chars = [\u2028];
separator_paragraph_chars = [\u2029];
space = [ \xa0\u1680\u2000-\u200a\u202f\u205f\u3000];

non_space = [^ \u00a0\u1680\u180e\u2000-\u200a\u202f\u3000\u0000-\u001f\u007f-\u009f];

single_quote = [\u0027];
double_quote = [\u0022];

letter = {letter_lower_chars}|{letter_upper_chars}|{letter_title_chars}|{letter_other_alpha_chars}|{hebrew_letter_chars};
latinish_letter = {letter_lower_chars}|{letter_upper_chars}|{letter_title_chars};

underscore = [_];

hyphen = [\-];
minus = [\u2212];
figure_dash = [\u2012];
ndash = [\u2013];
mdash = [\u2014\u2e3a\u2e3b\ufe31\ufe58];
hbar = [\u2015];
swung_dash = [\u2053];


other_non_breaking_dash = [\u058a\u05be\u1400\u1806\u2010-\u2013\u2212\u2e17\u2e1a\ufe32\ufe63\uff0d];

non_breaking_dash = (({hyphen}{1,1})|{other_non_breaking_dash});
breaking_dash = ({mdash}|{hbar}|{swung_dash}|({hyphen}{2,}));

// WB5
basic_word = {letter}+;
// WB6
word_non_breaking_mid_char = {letter}+(({mid_letter_chars}|{non_breaking_dash}|{mid_num_letter_chars}|{single_quote}){letter}+)+;
// WB7
word_end_single_quote = {letter}+(({mid_letter_chars}|{mid_num_letter_chars}){letter}+{single_quote});
// WB7a
hebrew_word_single_quote = ({hebrew_letter_chars}+{single_quote})+;
// WB7b and WB7c
hebrew_word_double_quote = ({hebrew_letter_chars}+{double_quote})+{hebrew_letter_chars}*;

// WB11 and WB12 (modified slightly)
possible_numeric_chars = ({numeric_chars}|{letter}|{non_breaking_dash}|{hyphen}|{mid_num_letter_chars}|{single_quote});
number = ({non_breaking_dash}?((({numeric_chars}|{number_or_digit_chars})+({mid_number_chars}|{mid_num_letter_chars}))*)({numeric_chars}|{number_or_digit_chars})+);
numeric = (({non_breaking_dash}|((({numeric_chars}|{number_or_digit_chars}|{letter})+{possible_numeric_chars}*)*))({numeric_chars}|{number_or_digit_chars})+({possible_numeric_chars}*({numeric_chars}|{number_or_digit_chars}|{letter})+)*);


// WB13
katakana = {katakana_chars}+;

// WB13a and WB13b
word_extend_num_letter = ({letter}|{numeric_chars}|{katakana}|{extend_num_letter_chars})+{extend_num_letter_chars}({letter}|{numeric_chars}|{katakana}|{extend_num_letter_chars})*;

possible_word_char = {letter}|{mark_spacing_combining_chars}|{mark_enclosing_chars}|{mark_nonspacing_chars}|{punct_connector_chars}|{currency_symbol_chars}|{symbol_modifier_chars}|{symbol_math_chars}|{symbol_other_chars}|{digit};
any_word = (({possible_word_char}*{letter}+{possible_word_char}*{non_breaking_dash})*{possible_word_char}*{letter}+{possible_word_char}*);

// GB6, GB7 & GB8
hangul_syllable = (({hangul_syllable_class_L}(hangul_syllable_class_L|hangul_syllable_class_V|hangul_syllable_class_LV|hangul_syllable_class_LVT))|(({hangul_syllable_class_L}|{hangul_syllable_class_V})({hangul_syllable_class_V}{hangul_syllable_class_T}))|(({hangul_syllable_class_LVT}|{hangul_syllable_class_T}){hangul_syllable_class_T}));

apos_word = ("'"?({latinish_letter}+"'"){latinish_letter}+"'"?);

ellipsis = ("\."{2,}|"\u2026");

acronym = ({letter}"\."){2,}{letter}?;
multi_punct_abbreviation = ({letter}+"\.")+{letter}*;

abbrev_word = (({letter}|{possible_word_char})+"\.")+({letter}|{possible_word_char})*;

abbreviation_plus_hyphen = ((({abbrev_word}|{any_word})({hyphen}|{ndash}))+({any_word}));

word = ({basic_word})|({word_non_breaking_mid_char})|({word_end_single_quote})|({hebrew_word_single_quote})|({hebrew_word_double_quote})|({word_extend_num_letter});

us_phone_number = ("\+"?"1"[\-\. ]?)?"\("?([2-9][0-8][0-9])"\)"?[\-\. ]?([2-9][0-9]{2})[\-\. ]?([0-9]{4});
international_phone_number = "\+"("9"[976][0-9]|"8"[987530][0-9]|"6"[987][0-9]|"5"[90][0-9]|"420-9"|"3"[875][0-9]|"2"[98654321][0-9]|"9"[8543210]|"8"[6421]|"6"[6543210]|"5"[87654321]|"4"[987654310]|"3"[9643210]|"2"[70]|"7"|"1"){space}*(([()\.\-/ ]{0,1}[0-9]){9}[0-9]{1,2});

url = ('http''s'?":"("/"{1,3}|[A-Za-z0-9%]))([^\u0000 \t\u00A0\u2000-\u200A\u3000\r\n\f<>{}\[\]]+);

email = ([a-zA-Z0-9\._%+\-]+"@"([a-zA-Z0-9]+([\-][a-zA-Z0-9]+)*[\.])+[a-zA-Z0-9]{2,3});

invalid_chars = ({control_chars}|{other_format_chars}|{other_private_use_chars});

"\u0000"                        { return TOKEN_TYPE_END; }
{invalid_chars}                 { return TOKEN_TYPE_INVALID_CHAR; }
{space}+                        { return TOKEN_TYPE_WHITESPACE; }

{email}                         { return TOKEN_TYPE_EMAIL; }
{url}                           { return TOKEN_TYPE_URL; }
{emoji}                         { return TOKEN_TYPE_EMOJI; }

{ellipsis}                      { return TOKEN_TYPE_ELLIPSIS; }

{us_phone_number}               { return TOKEN_TYPE_US_PHONE; }
{international_phone_number}    { return TOKEN_TYPE_INTL_PHONE; }

{abbreviation_plus_hyphen}      { return TOKEN_TYPE_WORD; }
{acronym}                       { return TOKEN_TYPE_ACRONYM; }

{number}                        { return TOKEN_TYPE_NUMERIC; }
{numeric}                       { return TOKEN_TYPE_NUMERIC; }
{apos_word}                     { return TOKEN_TYPE_WORD; }
{hangul_syllable}               { return TOKEN_TYPE_HANGUL_SYLLABLE; }
{ideographic_chars}             { return TOKEN_TYPE_IDEOGRAPHIC_CHAR; }
{ideographic_numeric_chars}     { return TOKEN_TYPE_IDEOGRAPHIC_NUMBER; }
{word}                          { return TOKEN_TYPE_WORD; }
{katakana}                      { return TOKEN_TYPE_WORD; }
{any_word}                      { return TOKEN_TYPE_WORD; }

{newline}                       { return TOKEN_TYPE_NEWLINE; }
"\."                            { return TOKEN_TYPE_PERIOD; }
"!"                             { return TOKEN_TYPE_EXCLAMATION; }
"?"                             { return TOKEN_TYPE_QUESTION_MARK; }
{hyphen}{1}                     { return TOKEN_TYPE_HYPHEN; }
","                             { return TOKEN_TYPE_COMMA; }
":"                             { return TOKEN_TYPE_COLON; }
";"                             { return TOKEN_TYPE_SEMICOLON; }
{punct_open_chars}              { return TOKEN_TYPE_PUNCT_OPEN; }
{punct_close_chars}             { return TOKEN_TYPE_PUNCT_CLOSE; }
"/"                             { return TOKEN_TYPE_SLASH; }
"\\"                            { return TOKEN_TYPE_BACKSLASH; }
"\""                            { return TOKEN_TYPE_DOUBLE_QUOTE; }
"'"                             { return TOKEN_TYPE_SINGLE_QUOTE; }
{punct_initial_quote_chars}     { return TOKEN_TYPE_OPEN_QUOTE; }
{punct_final_quote_chars}       { return TOKEN_TYPE_CLOSE_QUOTE; }
"&"                             { return TOKEN_TYPE_AMPERSAND; }
">"                             { return TOKEN_TYPE_GREATER_THAN; }
"<"                             { return TOKEN_TYPE_LESS_THAN; }
"@"                             { return TOKEN_TYPE_AT_SIGN; }
"+"                             { return TOKEN_TYPE_PLUS; }
"#"                             { return TOKEN_TYPE_POUND; }
{other_non_breaking_dash}       { return TOKEN_TYPE_DASH; }
{breaking_dash}                 { return TOKEN_TYPE_BREAKING_DASH; }
{other_surrogate_chars}         { return TOKEN_TYPE_INVALID_CHAR; }
{any}                           { return TOKEN_TYPE_OTHER; }
*/

}

inline scanner_t scanner_from_string(const char *input, size_t len) {
    const unsigned char *s = (const unsigned char *)input;

    scanner_t scanner;
    scanner.src = s;
    scanner.cursor = s;
    scanner.start = s;
    scanner.end = s + len;

    return scanner;
}

void tokenize_add_tokens(token_array *tokens, const char *input, size_t len) {
    scanner_t scanner = scanner_from_string(input, len);

    size_t token_start, token_length;
    uint16_t token_type;

    size_t consumed = 0;

    while (consumed < len) {
        token_type = scan_token(&scanner);

        token_start = scanner.start - scanner.src;
        token_length = scanner.cursor - scanner.start;

        if (token_length == 0) break;

        token_t token;
        token.offset = token_start;
        token.len = token_length;
        token.type = token_type;

        token_array_push(tokens, token);

        consumed += token_length;
    }

}

token_array *tokenize(const char *input) {

    token_array *tokens = token_array_new();

    tokenize_add_tokens(tokens, input, strlen(input));

    return tokens;
}
