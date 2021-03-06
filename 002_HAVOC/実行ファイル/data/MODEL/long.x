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
 38;
 -114.62125;296.74689;134.36339;,
 -113.73531;296.75629;134.72771;,
 -113.81848;297.09271;133.97246;,
 -114.62125;296.74689;134.36339;,
 -114.31937;296.41364;135.20921;,
 -114.62125;296.74689;134.36339;,
 -115.13071;296.32111;135.05406;,
 -114.62125;296.74689;134.36339;,
 -115.55821;296.54926;134.37846;,
 -114.62125;296.74689;134.36339;,
 -115.28041;296.92645;133.69218;,
 -114.62125;296.74689;134.36339;,
 -114.50572;297.16742;133.51103;,
 -114.62125;296.74689;134.36339;,
 -113.81848;297.09271;133.97246;,
 -0.49438;-274.79291;-130.88908;,
 37.24181;-258.54147;-149.29918;,
 41.14425;-274.31659;-113.76981;,
 -0.49438;-274.79291;-130.88908;,
 13.69198;-290.45032;-91.13145;,
 -0.49438;-274.79291;-130.88908;,
 -24.44278;-294.79419;-98.43181;,
 -0.49438;-274.79291;-130.88908;,
 -44.54382;-284.07666;-130.17300;,
 -0.49438;-274.79291;-130.88908;,
 -31.47474;-266.36853;-162.45384;,
 -0.49438;-274.79291;-130.88908;,
 4.92335;-255.00420;-170.96574;,
 -0.49438;-274.79291;-130.88908;,
 37.24181;-258.54147;-149.29918;,
 -19.18745;202.82970;125.49162;,
 -26.66447;233.03349;57.14986;,
 -71.88860;171.51384;168.86009;,
 -145.08240;162.66707;154.59685;,
 -183.65295;182.95195;93.44258;,
 -158.55557;217.09306;31.44849;,
 -88.68910;239.38177;15.29667;,
 -26.66447;233.03349;57.14986;;
 
 28;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,17;,
 3;18,17,19;,
 3;20,19,21;,
 3;22,21,23;,
 3;24,23,25;,
 3;26,25,27;,
 3;28,27,29;,
 4;30,17,16,31;,
 4;31,2,1,30;,
 4;32,19,17,30;,
 4;30,1,4,32;,
 4;33,21,19,32;,
 4;32,4,6,33;,
 4;34,23,21,33;,
 4;33,6,8,34;,
 4;35,25,23,34;,
 4;34,8,10,35;,
 4;36,27,25,35;,
 4;35,10,12,36;,
 4;37,29,27,36;,
 4;36,12,14,37;;
 
 MeshMaterialList {
  2;
  28;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;0.561000;0.949000;0.625000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.150000;0.084150;0.142350;;
  }
  Material {
   0.483200;0.483200;0.483200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  30;
  -0.180985;0.891252;0.415830;,
  0.191707;0.960387;0.202249;,
  0.225518;0.813260;0.536423;,
  -0.034173;0.668560;0.742873;,
  -0.382311;0.633333;0.672851;,
  -0.564548;0.729963;0.385278;,
  -0.449008;0.889222;0.087616;,
  -0.113144;0.993578;0.001262;,
  0.181084;-0.891323;-0.415634;,
  0.181081;-0.891322;-0.415637;,
  0.181089;-0.891321;-0.415637;,
  0.181096;-0.891318;-0.415640;,
  0.181096;-0.891320;-0.415635;,
  0.181096;-0.891323;-0.415630;,
  0.181090;-0.891324;-0.415630;,
  0.181090;-0.891322;-0.415635;,
  0.746894;0.608448;-0.268218;,
  0.828342;0.277869;0.486454;,
  0.244613;-0.055760;0.968016;,
  -0.562139;-0.141723;0.814809;,
  -0.985971;0.083763;0.144375;,
  -0.709768;0.451840;-0.540435;,
  0.061100;0.685841;-0.725182;,
  0.935827;-0.056162;0.347958;,
  0.849270;0.294439;-0.438231;,
  0.328528;-0.416281;0.847809;,
  -0.515344;-0.514835;0.685102;,
  -0.960532;-0.277606;-0.017720;,
  -0.671681;0.116871;-0.731564;,
  0.133839;0.371483;-0.918742;;
  28;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,1,7;,
  3;15,8,9;,
  3;15,9,10;,
  3;15,10,11;,
  3;15,11,12;,
  3;15,12,13;,
  3;15,13,14;,
  3;15,14,8;,
  4;17,23,24,16;,
  4;16,1,2,17;,
  4;18,25,23,17;,
  4;17,2,3,18;,
  4;19,26,25,18;,
  4;18,3,4,19;,
  4;20,27,26,19;,
  4;19,4,5,20;,
  4;21,28,27,20;,
  4;20,5,6,21;,
  4;22,29,28,21;,
  4;21,6,7,22;,
  4;16,24,29,22;,
  4;22,7,1,16;;
 }
 MeshTextureCoords {
  38;
  0.071430;0.000000;,
  0.142860;0.000000;,
  0.000000;0.000000;,
  0.214290;0.000000;,
  0.285710;0.000000;,
  0.357140;0.000000;,
  0.428570;0.000000;,
  0.500000;0.000000;,
  0.571430;0.000000;,
  0.642860;0.000000;,
  0.714290;0.000000;,
  0.785710;0.000000;,
  0.857140;0.000000;,
  0.928570;0.000000;,
  1.000000;0.000000;,
  0.071430;1.000000;,
  0.000000;1.000000;,
  0.142860;1.000000;,
  0.214290;1.000000;,
  0.285710;1.000000;,
  0.357140;1.000000;,
  0.428570;1.000000;,
  0.500000;1.000000;,
  0.571430;1.000000;,
  0.642860;1.000000;,
  0.714290;1.000000;,
  0.785710;1.000000;,
  0.857140;1.000000;,
  0.928570;1.000000;,
  1.000000;1.000000;,
  0.142860;0.134090;,
  0.000000;0.134840;,
  0.285710;0.136070;,
  0.428570;0.139300;,
  0.571430;0.141340;,
  0.714290;0.140650;,
  0.857140;0.137760;,
  1.000000;0.134840;;
 }
}
