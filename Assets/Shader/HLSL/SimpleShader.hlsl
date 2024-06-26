truct vs_in {
    float2 position_local : POS;
};

struct vs_out {
    float4 position_clip : SV_POSITION;
};

vs_out vs_main(vs_in input) {
  vs_out output = (vs_out)0; // zero the memory first
  output.position_clip = float4(input.position_local, 0.0, 1.0);
  return output;
}

float4 ps_main(vs_out input) : SV_TARGET {
  return float4( 1.0, 0.0, 1.0, 1.0 );
}