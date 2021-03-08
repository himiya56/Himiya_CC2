xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 233;
 66.05400;37.14600;112.49460;,
 44.21340;34.51260;167.66940;,
 49.23120;13.13100;168.99240;,
 69.66780;20.41860;113.16780;,
 44.21340;34.51260;167.66940;,
 12.74400;32.59320;191.35680;,
 12.74400;20.04360;191.35680;,
 49.23120;13.13100;168.99240;,
 16.72500;0.65760;168.64980;,
 37.51620;3.24900;170.82780;,
 12.52740;13.38960;-0.10260;,
 19.32480;9.14100;-0.39960;,
 21.55380;4.82220;-0.42720;,
 12.81660;4.92360;-0.27180;,
 6.88380;5.18100;-0.09240;,
 5.19000;15.00000;0.00000;,
 22.76580;-0.39660;-0.09120;,
 13.06440;-0.80460;-0.05400;,
 6.98100;-1.04400;-0.15120;,
 16.23600;51.05100;168.57660;,
 44.21340;34.51260;167.66940;,
 59.14320;51.06180;111.58740;,
 37.67880;64.98000;110.49600;,
 39.02100;-16.87200;109.86720;,
 48.48420;-14.46900;111.48360;,
 37.51620;3.24900;170.82780;,
 16.72500;0.65760;168.64980;,
 21.78660;-6.07680;-0.26520;,
 16.30860;-11.41020;-0.28920;,
 13.39500;-12.04020;-0.27960;,
 13.23900;-6.74820;-0.17340;,
 7.16760;-13.04580;-0.26460;,
 7.08120;-7.51500;-0.21300;,
 49.23120;13.13100;168.99240;,
 48.48420;-14.46900;111.48360;,
 65.77140;0.78480;113.77320;,
 16.23600;51.05100;168.57660;,
 14.25600;70.50300;109.93080;,
 49.23120;13.13100;168.99240;,
 16.72500;0.65760;168.64980;,
 19.18380;-19.24200;109.93080;,
 44.21340;34.51260;167.66940;,
 59.14320;51.06180;111.58740;,
 44.21340;34.51260;167.66940;,
 16.23600;51.05100;168.57660;,
 0.71940;15.61140;0.00600;,
 0.88320;5.08800;-0.09300;,
 0.97980;-1.13700;-0.15240;,
 -0.00180;52.37640;168.53101;,
 -0.00180;35.53140;191.35680;,
 -0.00180;20.04360;191.35680;,
 -0.00180;0.73980;168.60600;,
 -0.00180;52.37640;168.53101;,
 16.23600;51.05100;168.57660;,
 -0.00180;72.49980;109.93080;,
 -0.00180;-19.24200;109.93080;,
 16.72500;0.65760;168.64980;,
 -0.00180;0.73980;168.60600;,
 1.16580;-13.13880;-0.26520;,
 1.07880;-7.50120;-0.21240;,
 -63.60240;37.14600;108.87180;,
 -67.21620;20.41860;111.28200;,
 -44.12760;13.13100;168.99240;,
 -41.76120;34.51260;167.66940;,
 -41.76120;34.51260;167.66940;,
 -44.12760;13.13100;168.99240;,
 -12.74760;20.04360;191.35680;,
 -12.74760;32.59320;191.35680;,
 -28.58520;3.24900;168.58080;,
 -16.72860;0.65760;168.64980;,
 -11.01360;13.02420;-0.10560;,
 -11.04000;4.55340;-0.27420;,
 -19.00140;4.19220;-0.43380;,
 -16.90740;8.57820;-0.40500;,
 -3.72960;14.86200;-0.00120;,
 -5.11800;4.99500;-0.09420;,
 -11.10960;-1.18080;-0.05820;,
 -20.12580;-0.36720;0.38340;,
 -5.02140;-1.23000;-0.15300;,
 -16.23960;51.05100;168.57660;,
 -38.08740;64.91220;109.64640;,
 -56.69160;51.06180;108.83040;,
 -41.76120;34.51260;167.66940;,
 -33.07860;-16.87200;109.86720;,
 -16.72860;0.65760;168.64980;,
 -28.58520;3.24900;168.58080;,
 -46.03200;-14.46900;109.80240;,
 -18.97080;-6.01080;-0.15840;,
 -11.17440;-6.42780;-0.06420;,
 -9.30600;-11.69340;-0.16980;,
 -13.33020;-11.17140;-0.18120;,
 -4.92120;-7.70100;-0.21420;,
 -4.90980;-12.53400;-0.15360;,
 -44.12760;13.13100;168.99240;,
 -63.31920;0.78480;109.68420;,
 -46.03200;-14.46900;109.80240;,
 -16.23960;51.05100;168.57660;,
 -14.25960;70.50300;109.93080;,
 -44.12760;13.13100;168.99240;,
 -16.72860;0.65760;168.64980;,
 -19.18740;-19.24200;109.93080;,
 -41.76120;34.51260;167.66940;,
 -56.69160;51.06180;108.83040;,
 -41.76120;34.51260;167.66940;,
 -16.23960;51.05100;168.57660;,
 -16.23960;51.05100;168.57660;,
 -16.72860;0.65760;168.64980;,
 59.14320;51.06180;79.43940;,
 66.05400;37.14600;79.40040;,
 66.05400;37.14600;49.94700;,
 59.14320;51.06180;49.90680;,
 69.66780;20.41860;79.48800;,
 69.66780;20.41860;52.35840;,
 59.14320;51.06180;79.43940;,
 59.14320;51.06180;49.90680;,
 37.45140;65.01780;50.73180;,
 37.56240;64.99920;79.89480;,
 37.67880;64.98000;110.49600;,
 14.25600;70.50300;51.00720;,
 14.25600;70.50300;80.49540;,
 48.48420;-14.46900;80.48520;,
 39.02100;-16.87200;109.86720;,
 38.99220;-16.62120;80.77980;,
 38.96220;-16.36380;50.92920;,
 48.48420;-14.46900;50.87820;,
 19.18380;-19.24200;81.37200;,
 19.18380;-19.24200;51.00720;,
 48.48420;-14.46900;80.48520;,
 48.48420;-14.46900;50.87820;,
 66.46140;2.94300;50.80980;,
 66.14400;1.95000;79.79700;,
 65.77140;0.78480;113.77320;,
 -0.00180;72.58920;51.00720;,
 -0.00180;72.54420;80.87760;,
 -0.00180;-19.24200;81.91740;,
 -0.00180;-19.24200;51.00720;,
 -63.60240;37.14600;83.08740;,
 -56.69160;51.06180;82.73280;,
 -56.69160;51.06180;49.90680;,
 -63.60240;37.14600;49.94700;,
 -67.21620;20.41860;83.37960;,
 -67.21620;20.41860;52.35840;,
 -37.36020;65.03340;82.02540;,
 -37.45500;65.01780;50.73180;,
 -56.69160;51.06180;49.90680;,
 -56.69160;51.06180;82.73280;,
 -37.27740;65.04720;109.65840;,
 -14.25960;70.50300;81.30660;,
 -14.25960;70.50300;51.00720;,
 -32.79060;-16.63860;82.82040;,
 -33.07860;-16.87200;109.86720;,
 -46.03200;-14.46900;83.17260;,
 -46.03200;-14.46900;50.87820;,
 -32.45100;-16.36380;50.92920;,
 -19.18740;-19.24200;82.46400;,
 -19.18740;-19.24200;51.00720;,
 -63.62700;1.74540;83.48940;,
 -64.00980;2.94300;50.80980;,
 -46.03200;-14.46900;50.87820;,
 -46.03200;-14.46900;83.17260;,
 -63.31920;0.78480;109.68420;,
 46.32780;38.29860;18.22980;,
 51.76620;27.53220;18.25980;,
 53.35620;13.99920;18.41460;,
 46.32780;38.29860;18.22980;,
 29.26020;48.61980;18.46620;,
 11.34480;52.89780;18.80640;,
 38.44980;-12.65040;19.12260;,
 31.14000;-14.17020;19.30740;,
 15.71520;-16.53900;19.68480;,
 38.44980;-12.65040;19.12260;,
 51.96300;0.78000;18.63180;,
 0.32280;54.71880;19.02720;,
 0.61500;-16.64880;20.02380;,
 -50.99700;28.55280;20.54160;,
 -45.23640;39.59040;20.25780;,
 -52.33620;14.34240;20.77140;,
 -29.22540;49.66680;19.75860;,
 -45.23640;39.59040;20.25780;,
 -10.77900;53.32620;19.29540;,
 -25.50600;-14.53260;20.57760;,
 -36.37800;-13.08300;20.80020;,
 -14.66100;-16.75800;20.36700;,
 -50.96340;0.73380;20.93220;,
 -36.37800;-13.08300;20.80020;,
 40.59840;19.99740;6.94920;,
 21.55380;4.82220;-0.42720;,
 19.32480;9.14100;-0.39960;,
 36.28980;28.32960;6.92460;,
 41.87340;9.44220;7.04160;,
 22.76580;-0.39660;-0.09120;,
 36.28980;28.32960;6.92460;,
 19.32480;9.14100;-0.39960;,
 12.52740;13.38960;-0.10260;,
 22.86720;36.02280;7.03680;,
 5.19000;15.00000;0.00000;,
 8.93640;39.10380;7.20540;,
 24.58020;-12.54180;7.52100;,
 13.39500;-12.04020;-0.27960;,
 16.30860;-11.41020;-0.28920;,
 30.24840;-11.34840;7.42680;,
 12.57180;-14.41920;7.71360;,
 7.16760;-13.04580;-0.26460;,
 30.24840;-11.34840;7.42680;,
 16.30860;-11.41020;-0.28920;,
 21.78660;-6.07680;-0.26520;,
 40.73040;-0.96660;7.16760;,
 0.71940;15.61140;0.00600;,
 0.43500;40.41360;7.31400;,
 0.88740;-14.53980;7.88280;,
 1.16580;-13.13880;-0.26520;,
 -34.54620;28.59900;7.94220;,
 -16.90740;8.57820;-0.40500;,
 -19.00140;4.19220;-0.43380;,
 -38.92260;20.08080;8.09460;,
 -20.12580;-0.36720;0.38340;,
 -39.48120;9.40560;8.21400;,
 -22.26480;36.31320;7.68420;,
 -11.01360;13.02420;-0.10560;,
 -16.90740;8.57820;-0.40500;,
 -34.54620;28.59900;7.94220;,
 -8.09340;39.23160;7.44960;,
 -3.72960;14.86200;-0.00120;,
 -27.52200;-11.38740;8.25960;,
 -13.33020;-11.17140;-0.18120;,
 -9.30600;-11.69340;-0.16980;,
 -19.33500;-12.46800;8.15340;,
 -4.90980;-12.53400;-0.15360;,
 -10.89840;-14.15220;8.04900;,
 -38.62500;-0.96420;8.31000;,
 -18.97080;-6.01080;-0.15840;,
 -13.33020;-11.17140;-0.18120;,
 -27.52200;-11.38740;8.25960;;
 
 156;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;7,6,8,9;,
 4;10,11,12,13;,
 4;10,13,14,15;,
 4;13,12,16,17;,
 4;13,17,18,14;,
 4;19,20,21,22;,
 4;23,24,25,26;,
 4;27,28,29,30;,
 4;27,30,17,16;,
 4;30,29,31,32;,
 4;30,32,18,17;,
 4;33,25,34,35;,
 3;36,22,37;,
 3;38,35,3;,
 3;39,40,23;,
 3;41,0,42;,
 3;43,44,5;,
 4;45,15,14,46;,
 4;46,14,18,47;,
 4;48,49,5,44;,
 4;49,50,6,5;,
 4;50,51,8,6;,
 4;52,53,37,54;,
 4;55,40,56,57;,
 4;58,59,32,31;,
 4;59,47,18,32;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;65,68,69,66;,
 4;70,71,72,73;,
 4;70,74,75,71;,
 4;71,76,77,72;,
 4;71,75,78,76;,
 4;79,80,81,82;,
 4;83,84,85,86;,
 4;87,88,89,90;,
 4;87,77,76,88;,
 4;88,91,92,89;,
 4;88,76,78,91;,
 4;93,94,95,85;,
 3;96,97,80;,
 3;98,61,94;,
 3;99,83,100;,
 3;101,102,60;,
 3;103,67,104;,
 4;45,46,75,74;,
 4;46,47,78,75;,
 4;48,104,67,49;,
 4;49,67,66,50;,
 4;50,66,69,51;,
 4;52,54,97,105;,
 4;55,57,106,100;,
 4;58,92,91,59;,
 4;59,91,78,47;,
 4;107,42,0,108;,
 4;107,108,109,110;,
 4;108,0,3,111;,
 4;108,111,112,109;,
 4;113,114,115,116;,
 4;113,116,117,21;,
 4;116,115,118,119;,
 4;116,119,37,117;,
 4;120,24,121,122;,
 4;120,122,123,124;,
 4;122,121,40,125;,
 4;122,125,126,123;,
 4;127,128,129,130;,
 4;127,130,131,34;,
 4;130,129,112,111;,
 4;130,111,3,131;,
 4;119,118,132,133;,
 4;119,133,54,37;,
 4;125,40,55,134;,
 4;125,134,135,126;,
 4;136,60,102,137;,
 4;136,137,138,139;,
 4;140,61,60,136;,
 4;140,136,139,141;,
 4;142,143,144,145;,
 4;142,145,81,146;,
 4;147,148,143,142;,
 4;147,142,146,97;,
 4;149,150,86,151;,
 4;149,151,152,153;,
 4;154,100,150,149;,
 4;154,149,153,155;,
 4;156,157,158,159;,
 4;156,159,95,160;,
 4;140,141,157,156;,
 4;140,156,160,61;,
 4;133,132,148,147;,
 4;133,147,97,54;,
 4;134,55,100,154;,
 4;134,154,155,135;,
 4;161,110,109,162;,
 4;162,109,112,163;,
 4;164,165,115,114;,
 4;165,166,118,115;,
 4;167,124,123,168;,
 4;168,123,126,169;,
 4;170,171,129,128;,
 4;171,163,112,129;,
 4;166,172,132,118;,
 4;169,126,135,173;,
 4;174,139,138,175;,
 4;176,141,139,174;,
 4;177,178,144,143;,
 4;179,177,143,148;,
 4;180,153,152,181;,
 4;182,155,153,180;,
 4;183,184,158,157;,
 4;176,183,157,141;,
 4;172,179,148,132;,
 4;173,135,155,182;,
 4;185,186,187,188;,
 4;185,188,161,162;,
 4;189,190,186,185;,
 4;189,185,162,163;,
 4;191,192,193,194;,
 4;191,194,165,164;,
 4;194,193,195,196;,
 4;194,196,166,165;,
 4;197,198,199,200;,
 4;197,200,167,168;,
 4;201,202,198,197;,
 4;201,197,168,169;,
 4;203,204,205,206;,
 4;203,206,171,170;,
 4;206,205,190,189;,
 4;206,189,163,171;,
 4;196,195,207,208;,
 4;196,208,172,166;,
 4;209,210,202,201;,
 4;209,201,169,173;,
 4;211,212,213,214;,
 4;211,214,174,175;,
 4;214,213,215,216;,
 4;214,216,176,174;,
 4;217,218,219,220;,
 4;217,220,178,177;,
 4;221,222,218,217;,
 4;221,217,177,179;,
 4;223,224,225,226;,
 4;223,226,180,181;,
 4;226,225,227,228;,
 4;226,228,182,180;,
 4;229,230,231,232;,
 4;229,232,184,183;,
 4;216,215,230,229;,
 4;216,229,183,176;,
 4;208,207,222,221;,
 4;208,221,179,172;,
 4;228,227,210,209;,
 4;228,209,173,182;;
 
 MeshMaterialList {
  3;
  156;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.006400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  161;
  0.015736;0.147374;-0.988956;,
  -0.006787;0.004471;-0.999967;,
  0.000996;0.004981;-0.999987;,
  -0.000028;0.012035;-0.999928;,
  0.121499;0.132786;-0.983670;,
  0.716176;0.648384;-0.258245;,
  0.725964;0.661451;0.188304;,
  0.143729;0.030062;-0.989160;,
  0.922814;0.302338;-0.238759;,
  0.923819;0.336324;0.182877;,
  0.176817;-0.011309;-0.984179;,
  0.975482;0.006518;-0.219981;,
  0.983944;0.017485;0.177621;,
  0.224482;-0.228431;-0.947326;,
  0.462093;-0.881116;-0.100526;,
  0.435715;-0.884532;0.166601;,
  0.692948;0.477211;0.540455;,
  0.275712;0.846960;0.454578;,
  0.309442;0.430058;0.848113;,
  0.753429;-0.268141;0.600371;,
  0.227648;-0.353378;0.907359;,
  0.351012;-0.790844;0.501354;,
  0.100218;-0.864528;0.492492;,
  0.173805;0.972213;0.156823;,
  0.180487;0.951317;-0.249842;,
  0.059751;-0.984875;0.162635;,
  0.071747;-0.996266;-0.048034;,
  0.032252;0.138876;-0.989784;,
  -0.015407;-0.011160;-0.999819;,
  -0.003601;-0.006276;-0.999974;,
  -0.004909;0.016545;-0.999851;,
  0.371420;0.892817;-0.254803;,
  0.378860;0.909415;0.171550;,
  0.172224;-0.983402;-0.057098;,
  0.153706;-0.975186;0.159334;,
  0.002533;0.012160;-0.999923;,
  0.206068;-0.117409;-0.971469;,
  0.869986;-0.459634;-0.178498;,
  0.856576;-0.486359;0.172434;,
  -0.002086;0.018447;-0.999828;,
  -0.004064;0.147417;-0.989066;,
  -0.000000;0.009451;-0.999955;,
  -0.000009;0.009479;-0.999955;,
  -0.004217;0.003813;-0.999984;,
  0.000000;0.879347;0.476182;,
  0.000000;0.434390;0.900725;,
  0.000000;-0.419603;0.907708;,
  0.000000;-0.869734;0.493521;,
  0.000006;0.986763;0.162169;,
  0.001676;0.967737;-0.251955;,
  0.000000;-0.986624;0.163014;,
  0.001330;-0.999129;-0.041709;,
  -0.002119;0.006639;-0.999976;,
  -0.024130;0.148854;-0.988565;,
  0.006898;0.004718;-0.999965;,
  -0.002994;0.002595;-0.999992;,
  -0.009227;-0.000885;-0.999957;,
  -0.143527;0.134894;-0.980410;,
  -0.734144;0.631555;-0.249340;,
  -0.749527;0.636463;0.182003;,
  -0.173455;0.005319;-0.984827;,
  -0.925310;0.300908;-0.230770;,
  -0.929343;0.323102;0.178678;,
  -0.209963;-0.025408;-0.977379;,
  -0.976851;0.004563;-0.213872;,
  -0.982977;-0.001177;0.183725;,
  -0.233586;-0.244674;-0.941048;,
  -0.433038;-0.896678;-0.091901;,
  -0.416464;-0.891360;0.178983;,
  -0.722553;0.447447;0.526980;,
  -0.296302;0.840186;0.454194;,
  -0.331965;0.420328;0.844466;,
  -0.748144;-0.317951;0.582398;,
  -0.249562;-0.391870;0.885526;,
  -0.348807;-0.807520;0.475653;,
  -0.125669;-0.871367;0.474264;,
  -0.176396;0.971773;0.156658;,
  -0.177359;0.952155;-0.248887;,
  -0.085466;-0.982974;0.162661;,
  -0.101549;-0.993620;-0.049071;,
  -0.044894;0.140714;-0.989032;,
  0.008756;-0.022888;-0.999700;,
  -0.011745;-0.016064;-0.999802;,
  -0.000347;0.010173;-0.999948;,
  -0.392916;0.884249;-0.252428;,
  -0.415817;0.909448;0.000395;,
  -0.173156;-0.983519;-0.052027;,
  -0.177391;-0.970498;0.163296;,
  -0.388050;0.857667;0.337379;,
  -0.009332;0.003224;-0.999951;,
  -0.222351;-0.113135;-0.968380;,
  -0.869918;-0.461660;-0.173531;,
  -0.840479;-0.508212;0.187923;,
  -0.008484;0.017433;-0.999812;,
  0.745746;0.666230;-0.000397;,
  0.943799;0.330519;0.000000;,
  0.999927;0.012047;0.001105;,
  0.466498;-0.884496;-0.006816;,
  0.185967;0.982556;0.000311;,
  0.065728;-0.997835;-0.002174;,
  0.391877;0.920017;-0.000454;,
  0.176164;-0.984351;-0.004332;,
  0.874832;-0.484413;-0.003517;,
  0.000011;1.000000;0.000759;,
  0.000000;-1.000000;-0.000000;,
  -0.762957;0.646450;0.000350;,
  -0.943799;0.330519;0.000000;,
  -0.999931;0.011687;0.001213;,
  -0.438195;-0.898849;-0.007494;,
  -0.186245;0.982503;0.000428;,
  -0.094988;-0.995475;-0.002607;,
  -0.416130;0.909305;0.000399;,
  -0.175113;-0.984535;-0.005127;,
  -0.874025;-0.485867;-0.003640;,
  0.138841;0.757576;-0.637811;,
  0.075124;-0.986794;-0.143503;,
  0.555102;0.515958;-0.652418;,
  0.753795;0.224055;-0.617731;,
  0.816333;-0.003745;-0.577570;,
  0.438045;-0.850720;-0.290504;,
  0.280623;0.711050;-0.644716;,
  0.170719;-0.970858;-0.168193;,
  0.771872;-0.404124;-0.490814;,
  -0.001000;0.766430;-0.642326;,
  -0.001365;-0.991197;-0.132385;,
  -0.140854;0.757138;-0.637889;,
  -0.104585;-0.981516;-0.160273;,
  -0.576406;0.502901;-0.644086;,
  -0.764023;0.213465;-0.608852;,
  -0.820701;-0.010308;-0.571265;,
  -0.406459;-0.869280;-0.281323;,
  -0.301102;0.701967;-0.645430;,
  -0.167775;-0.970959;-0.170558;,
  -0.771867;-0.404120;-0.490824;,
  0.077488;0.464363;-0.882249;,
  0.078049;-0.975268;-0.206786;,
  0.328474;0.316031;-0.890073;,
  0.477383;0.135445;-0.868194;,
  0.542059;-0.007971;-0.840303;,
  0.378572;-0.783018;-0.493524;,
  0.158763;0.436067;-0.885799;,
  0.170609;-0.949058;-0.264918;,
  0.561606;-0.317699;-0.763980;,
  -0.006752;0.467054;-0.884203;,
  -0.016831;-0.983083;-0.182383;,
  -0.090919;0.463509;-0.881415;,
  -0.116323;-0.963765;-0.240056;,
  -0.355627;0.308028;-0.882410;,
  -0.503773;0.112476;-0.856482;,
  -0.560210;-0.019277;-0.828126;,
  -0.349101;-0.814463;-0.463443;,
  -0.183453;0.429460;-0.884256;,
  -0.159675;-0.952379;-0.259766;,
  -0.568254;-0.315804;-0.759839;,
  0.171160;-0.937391;-0.303320;,
  0.193199;-0.921078;-0.338066;,
  0.080417;-0.972022;-0.220696;,
  -0.028286;-0.982587;-0.183638;,
  -0.127130;-0.962096;-0.241265;,
  -0.155445;-0.947903;-0.278060;,
  -0.126158;-0.958508;-0.255631;;
  156;
  4;9,16,19,12;,
  4;16,18,20,19;,
  4;19,20,22,21;,
  4;27,4,7,28;,
  4;27,28,1,0;,
  4;28,7,10,29;,
  4;28,29,2,1;,
  4;17,16,6,32;,
  4;34,15,21,22;,
  4;36,13,30,39;,
  4;36,39,29,10;,
  4;39,30,3,35;,
  4;39,35,2,29;,
  4;19,21,15,38;,
  3;17,32,23;,
  3;19,38,12;,
  3;22,25,34;,
  3;16,9,6;,
  3;16,17,18;,
  4;40,0,1,41;,
  4;41,1,2,42;,
  4;44,45,18,17;,
  4;45,46,20,18;,
  4;46,47,22,20;,
  4;44,17,23,48;,
  4;50,25,22,47;,
  4;43,52,35,3;,
  4;52,42,2,35;,
  4;62,65,72,69;,
  4;69,72,73,71;,
  4;72,74,75,73;,
  4;80,81,60,57;,
  4;80,53,54,81;,
  4;81,82,63,60;,
  4;81,54,55,82;,
  4;70,88,59,69;,
  4;87,75,74,68;,
  4;90,93,83,66;,
  4;90,63,82,93;,
  4;93,89,56,83;,
  4;93,82,55,89;,
  4;72,92,68,74;,
  3;70,76,88;,
  3;72,65,92;,
  3;75,87,78;,
  3;69,59,62;,
  3;69,71,70;,
  4;40,41,54,53;,
  4;41,42,55,54;,
  4;44,70,71,45;,
  4;45,71,73,46;,
  4;46,73,75,47;,
  4;44,48,76,70;,
  4;50,47,75,78;,
  4;43,56,89,52;,
  4;52,89,55,42;,
  4;94,6,9,95;,
  4;94,95,8,5;,
  4;95,9,12,96;,
  4;95,96,11,8;,
  4;94,5,31,100;,
  4;94,100,32,6;,
  4;100,31,24,98;,
  4;100,98,23,32;,
  4;97,15,34,101;,
  4;97,101,33,14;,
  4;101,34,25,99;,
  4;101,99,26,33;,
  4;97,14,37,102;,
  4;97,102,38,15;,
  4;102,37,11,96;,
  4;102,96,12,38;,
  4;98,24,49,103;,
  4;98,103,48,23;,
  4;99,25,50,104;,
  4;99,104,51,26;,
  4;106,62,59,105;,
  4;106,105,58,61;,
  4;107,65,62,106;,
  4;107,106,61,64;,
  4;111,84,58,105;,
  4;111,105,59,85;,
  4;109,77,84,111;,
  4;109,111,85,76;,
  4;112,87,68,108;,
  4;112,108,67,86;,
  4;110,78,87,112;,
  4;110,112,86,79;,
  4;113,91,67,108;,
  4;113,108,68,92;,
  4;107,64,91,113;,
  4;107,113,92,65;,
  4;103,49,77,109;,
  4;103,109,76,48;,
  4;104,50,78,110;,
  4;104,110,79,51;,
  4;116,5,8,117;,
  4;117,8,11,118;,
  4;116,120,31,5;,
  4;120,114,24,31;,
  4;119,14,33,121;,
  4;121,33,26,115;,
  4;119,122,37,14;,
  4;122,118,11,37;,
  4;114,123,49,24;,
  4;115,26,51,124;,
  4;128,61,58,127;,
  4;129,64,61,128;,
  4;131,127,58,84;,
  4;125,131,84,77;,
  4;132,86,67,130;,
  4;126,79,86,132;,
  4;133,130,67,91;,
  4;129,133,91,64;,
  4;123,125,77,49;,
  4;124,51,79,126;,
  4;137,7,4,136;,
  4;137,136,116,117;,
  4;138,10,7,137;,
  4;138,137,117,118;,
  4;136,4,27,140;,
  4;136,140,120,116;,
  4;140,27,0,134;,
  4;140,134,114,120;,
  4;141,154,155,139;,
  4;141,139,119,121;,
  4;135,156,154,141;,
  4;135,141,121,115;,
  4;139,13,36,142;,
  4;139,142,122,119;,
  4;142,36,10,138;,
  4;142,138,118,122;,
  4;134,0,40,143;,
  4;134,143,123,114;,
  4;144,157,156,135;,
  4;144,135,115,124;,
  4;147,57,60,148;,
  4;147,148,128,127;,
  4;148,60,63,149;,
  4;148,149,129,128;,
  4;151,80,57,147;,
  4;151,147,127,131;,
  4;145,53,80,151;,
  4;145,151,131,125;,
  4;150,158,159,152;,
  4;150,152,132,130;,
  4;152,159,160,146;,
  4;152,146,126,132;,
  4;153,90,66,150;,
  4;153,150,130,133;,
  4;149,63,90,153;,
  4;149,153,133,129;,
  4;143,40,53,145;,
  4;143,145,125,123;,
  4;146,160,157,144;,
  4;146,144,124,126;;
 }
 MeshTextureCoords {
  233;
  0.666670;0.333330;,
  1.000000;0.333330;,
  1.000000;0.666670;,
  0.666670;0.666670;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.854100;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.807570;0.333330;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.666670;,
  0.814470;0.666670;,
  0.666670;0.666670;,
  0.848910;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.858730;0.333330;,
  0.798470;0.666670;,
  1.000000;0.666670;,
  1.000000;1.000000;,
  0.788510;1.000000;,
  1.000000;0.835740;,
  1.000000;1.000000;,
  0.869520;1.000000;,
  0.843590;0.843000;,
  0.666670;1.000000;,
  0.666670;0.846380;,
  1.000000;0.847180;,
  0.666670;1.000000;,
  0.666670;0.877260;,
  0.757790;0.000000;,
  0.666670;0.333330;,
  1.000000;0.756930;,
  0.727590;1.000000;,
  0.666670;0.666670;,
  1.000000;0.166670;,
  0.666670;0.000000;,
  0.000000;0.166670;,
  0.333330;0.000000;,
  0.562450;0.000000;,
  0.539770;0.333330;,
  0.544150;0.666670;,
  0.483210;0.000000;,
  0.491990;0.333330;,
  0.487360;0.666670;,
  0.472700;1.000000;,
  0.516790;0.000000;,
  0.666670;0.000000;,
  0.538160;0.333330;,
  0.531370;0.666670;,
  0.666670;1.000000;,
  0.527300;1.000000;,
  0.552580;1.000000;,
  0.548620;0.859220;,
  0.666670;0.333330;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.333330;0.333330;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.854100;0.000000;,
  0.807570;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  0.814470;0.666670;,
  1.000000;0.666670;,
  0.666670;0.666670;,
  0.848910;0.000000;,
  0.858730;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.798470;0.666670;,
  0.788510;1.000000;,
  1.000000;1.000000;,
  1.000000;0.666670;,
  1.000000;0.835740;,
  0.843590;0.843000;,
  0.869520;1.000000;,
  1.000000;1.000000;,
  0.666670;0.846380;,
  0.666670;1.000000;,
  1.000000;0.847180;,
  0.666670;0.877260;,
  0.666670;1.000000;,
  0.757790;0.000000;,
  0.666670;0.333330;,
  1.000000;0.756930;,
  0.727590;1.000000;,
  0.666670;0.666670;,
  1.000000;0.166670;,
  0.666670;0.000000;,
  0.000000;0.166670;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.492930;0.000000;,
  0.490300;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.482040;0.666670;,
  0.333330;0.666670;,
  1.000000;0.507070;,
  1.000000;0.666670;,
  0.852300;0.666670;,
  0.851420;0.504010;,
  0.850490;0.333330;,
  0.666670;0.666670;,
  0.666670;0.499850;,
  1.000000;0.496170;,
  0.865930;0.666670;,
  0.866810;0.502160;,
  0.867720;0.333330;,
  1.000000;0.333330;,
  0.666670;0.505110;,
  0.666670;0.333330;,
  0.496170;1.000000;,
  0.333330;1.000000;,
  0.333330;0.829610;,
  0.486790;0.826790;,
  0.666670;0.823480;,
  0.550310;0.666670;,
  0.544150;0.497690;,
  0.536410;0.508200;,
  0.541980;0.333330;,
  0.520800;0.333330;,
  0.519030;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.508820;0.666670;,
  0.333330;0.666670;,
  0.851340;0.489650;,
  0.852300;0.666670;,
  1.000000;0.666670;,
  1.000000;0.480970;,
  0.850490;0.333330;,
  0.666670;0.495260;,
  0.666670;0.666670;,
  0.866750;0.513700;,
  0.865930;0.666670;,
  1.000000;0.516020;,
  1.000000;0.333330;,
  0.867720;0.333330;,
  0.666670;0.511280;,
  0.666670;0.333330;,
  0.518360;0.826210;,
  0.333330;0.829610;,
  0.333330;1.000000;,
  0.516020;1.000000;,
  0.666670;0.823480;,
  0.146250;0.000000;,
  0.146390;0.333330;,
  0.139230;0.666670;,
  1.000000;0.853750;,
  0.853320;0.855990;,
  0.666670;0.855390;,
  1.000000;0.147680;,
  0.868720;0.148450;,
  0.666670;0.150110;,
  0.147680;1.000000;,
  0.145240;0.833070;,
  0.557140;0.854270;,
  0.547750;0.151860;,
  0.158390;0.333330;,
  0.156930;0.000000;,
  0.149830;0.666670;,
  0.853290;0.849260;,
  1.000000;0.843070;,
  0.666670;0.852860;,
  0.868680;0.155010;,
  1.000000;0.156360;,
  0.666670;0.153630;,
  0.157170;0.832850;,
  0.156360;1.000000;,
  0.060900;0.333330;,
  0.000000;0.333330;,
  0.000000;0.000000;,
  0.060650;0.000000;,
  0.056540;0.666670;,
  0.000000;0.666670;,
  1.000000;0.939350;,
  1.000000;1.000000;,
  0.854100;1.000000;,
  0.853780;0.941660;,
  0.666670;1.000000;,
  0.666670;0.941860;,
  0.869190;0.061420;,
  0.869520;0.000000;,
  1.000000;0.000000;,
  1.000000;0.061130;,
  0.666670;0.062080;,
  0.666670;0.000000;,
  0.061130;1.000000;,
  0.000000;1.000000;,
  0.000000;0.835740;,
  0.059900;0.834640;,
  0.562450;1.000000;,
  0.560320;0.941420;,
  0.550580;0.062820;,
  0.552580;0.000000;,
  0.065170;0.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.065970;0.333330;,
  0.000000;0.666670;,
  0.058940;0.666670;,
  0.853770;0.938790;,
  0.854100;1.000000;,
  1.000000;1.000000;,
  1.000000;0.934830;,
  0.666670;0.940780;,
  0.666670;1.000000;,
  1.000000;0.064260;,
  1.000000;0.000000;,
  0.869520;0.000000;,
  0.869170;0.063680;,
  0.666670;0.000000;,
  0.666670;0.063030;,
  0.064400;0.834560;,
  0.000000;0.835740;,
  0.000000;1.000000;,
  0.064260;1.000000;;
 }
}
