namespace hr {

namespace ads_game {

vector<ld> shape_rock = { -0.0176894, 0.0952504,  0.0278998, 0.0966286,  0.0686721, 0.0455547,  0.110983, 0.0122558,  0.0994024, -0.0483395,  0.0517039, -0.0802772,  -0.00271848, -0.0706804,  -0.0564861, -0.08575,  -0.100087, -0.0483411,  -0.100031, -0.0102072,  -0.0761486, 0.0292356,  -0.0639653, 0.077575 };
vector<ld> shape_rock2 = {-0.00204264, 0.111665, 0.0374777, 0.119247, 0.0797168, 0.0940249, 0.106214, 0.0326813, 0.121954, -0.0109009, 0.0837905, -0.0865154, 0.0517718, -0.108312, 0.00135972, -0.0802237, -0.0632991, -0.0837181, -0.0980407, -0.0510629, -0.122639, 0.00885725, -0.0817448, 0.0878757, };
vector<ld> shape_missile = { 0.04, 0, 0.01, -0.02, -0.02, -0.02, -0.02, 0.02, 0.01, 0.02, };
vector<ld> shape_particle = { 0.01, -0.01, -0.01, -0.01, -0.01, 0.01, 0.01, 0.01, };
vector<ld> shape_gold = {0.100344, 0.00161845, 0.0484642, -0.0177702, 0.0720984, -0.0698096, 0.0217039, -0.0468348, 0.00161845, -0.100344, -0.0177702, -0.0484642, -0.0698096, -0.0720984, -0.0468348, -0.0217039, -0.100344, -0.00161845, -0.0484642, 0.0177702, -0.0720984, 0.0698096, -0.0217039, 0.0468348, -0.00161845, 0.100344, 0.0177702, 0.0484642, 0.0698096, 0.0720984, 0.0468348, 0.0217039, };
vector<ld> shape_heart = {-0.102016, 3.74802e-17, -0.0451579, 0.0403539, 0.00865751, 0.0913848, 0.0500387, 0.0856432, 0.0769946, 0.0673703, 0.0817517, 0.0327007, 0.0537951, 0.00480313, 0.0537951, -0.00480313, 0.0817517, -0.0327007, 0.0769946, -0.0673703, 0.0500387, -0.0856432, 0.00865751, -0.0913848, -0.0451579, -0.0403539, -0.102016, -3.74802e-17, };
vector<ld> shape_weapon = {-0.0731165, 0.0596477, -0.047071, 0.0268977, 0.0807759, 0.0230788, 0.098148, 0.00288671, 0.098148, -0.00288671, 0.0807759, -0.0230788, -0.047071, -0.0268977, -0.0731165, -0.0596477, };
vector<ld> shape_fuel = {0.0802337, 0.0224383, 0.0802337, -0.0224383, 0.0224383, -0.0802337, -0.0224383, -0.0802337, -0.0802337, -0.0224383, -0.0802337, 0.0224383, -0.0224383, 0.0802337, 0.0224383, 0.0802337, };
vector<ld> shape_airtank = {-0.101054, 0.0134738, -0.0904219, 0.014429, -0.0779099, 0.0442451, 0.078873, 0.043284, 0.0894665, 0.0259742, 0.0894665, -0.0259742, 0.078873, -0.043284, -0.0779099, -0.0442451, -0.0904219, -0.014429, -0.101054, -0.0134738, };
vector<ld> shape_ship = { 0.0699706, 0, 0.0509304, 0.019032, 0.0056909, 0.023788, 0.0318813, 0.0309258, 0.0330715, 0.0368693, 0.00331668, 0.0380512, -0.0630665, 0.0699568, -0.0619577, 0.041535, -0.0678691, 0.0415233, -0.0678946, 0.0261072, -0.0572505, 0.0237463, -0.0572505, -0.0237463, -0.0678946, -0.0261072, -0.0678691, -0.0415233, -0.0619577, -0.041535, -0.0630665, -0.0699568, 0.00331668, -0.0380512, 0.0330715, -0.0368693, 0.0318813, -0.0309258, 0.0056909, -0.023788, 0.0509304, -0.019032 };
vector<ld> shape_turret = { 0.154282, 0.0304832, 0.134789, 0.0173922, 0.101045, 0.013638, 0.0836262, 0.0210614, 0.083667, 0.0489607, 0.0595074, 0.0812028, 0.00620363, 0.115388, -0.0862034, 0.0682185, -0.0544688, 0.0358999, -0.0544688, -0.0358999, -0.0862034, -0.0682185, 0.00620363, -0.115388, 0.0595074, -0.0812028, 0.083667, -0.0489607, 0.0836262, -0.0210614, 0.101045, -0.013638, 0.134789, -0.0173922, 0.154282, -0.0304832 };

const ld turret_length = 0; // 0.15;

struct ship_model: gi_extension {
  map<ld, hpcshape> ship_at_scale;
  };

const hpcshape& make_shape() {

  auto& mmd = (unique_ptr<ship_model>&) cgi.ext["ship_model"];
  if(!mmd) mmd = std::make_unique<ship_model> ();

  auto scale = DS_(scale);
  auto sas = at_or_null(mmd->ship_at_scale, scale);

  if(sas) return *sas;  

  auto& shShip = mmd->ship_at_scale[scale];

  cgi.bshape(shShip, PPR::MONSTER_BODY);
  int N = isize(shape_ship);

  vector<hyperpoint> lst;
  for(int i=0; i<N; i += 2) lst.push_back(normalize(hpxyz(shape_ship[i] * scale, shape_ship[i+1] * scale, 1)));
  for(auto h: lst) cgi.hpcpush(h);
  cgi.hpcpush(lst[0]);
  cgi.finishshape();
  cgi.extra_vertices();

  return shShip;
  }

}}
