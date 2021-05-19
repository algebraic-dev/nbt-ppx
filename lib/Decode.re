open DecodeTypes;

let decode_uncompressed = ic =>
  Bitstring.bitstring_of_string(ic) |> decode_payload;

let decode_zipped = string => {
  switch (Ezgzip.decompress(string)) {
  | Ok(x) => decode_uncompressed(x)
  | Error(_) => Error(`CannotUncompress)
  };
};
