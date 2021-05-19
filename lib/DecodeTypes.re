open Data;

let ( let* ) = Result.bind;

let decode_tag =
  fun%bitstring
  | {| 0 : 8; payload : -1 : bitstring |} => Ok((0, "", payload))
  | {| id : 8;
       name_len : 16 : bigendian;
       name: name_len*8 : string;
       payload : -1 : bitstring |} =>
    Ok((id, name, payload))
  | {| _ |} => Error(`NotATag);

let decode_byte =
  fun%bitstring
  | {| value : 8; payload : -1 : bitstring |} => Ok((TByte(value), payload))
  | {| _ |} => Error(`CannotDecode);

let decode_short =
  fun%bitstring
  | {| value : 16; payload : -1 : bitstring |} =>
    Ok((TShort(value), payload))
  | {| _ |} => Error(`CannotDecode);

let decode_int =
  fun%bitstring
  | {| value : 32 : bigendian; payload : -1 : bitstring |} =>
    Ok((TInt(value), payload))
  | {| _ |} => Error(`CannotDecode);

let decode_long =
  fun%bitstring
  | {| value : 64 : bigendian ; payload : -1 : bitstring |} =>
    Ok((TLong(value), payload))
  | {| _ |} => Error(`CannotDecode);

let decode_float =
  fun%bitstring
  | {| value : 32 : bigendian ; payload : -1 : bitstring |} =>
    Ok((TFloat(Int32.float_of_bits(value)), payload))
  | {| _ |} => Error(`CannotDecode);

let decode_double =
  fun%bitstring
  | {| value : 64 : bigendian ; payload : -1 : bitstring |} =>
    Ok((TDouble(Int64.float_of_bits(value)), payload))
  | {| _ |} => Error(`CannotDecode);

let decode_byte_array =
  fun%bitstring
  | {| length : 32 : bigendian ; bytes: Int32.to_int(length)*8 : string; payload : -1 : bitstring |} =>
    Ok((TByteArray(bytes), payload))
  | {| _ |} => Error(`CannotDecode);

let decode_string =
  fun%bitstring
  | {| length : 16 : bigendian ; str: length*8 : string; payload : -1 : bitstring |} =>
    Ok((TString(str), payload))
  | {| _ |} => Error(`CannotDecode);

let rec decode_list =
  fun%bitstring
  | {| type_id: 8 ; length : 32 : bigendian; payload : -1 : bitstring |} => {
      let rec loop = (length, payload) => {
        switch (length) {
        | 0 => Ok(([], payload))
        | l =>
          let* (ext, bits') = decode_ext_nbt(payload, type_id);
          let* (tail, payload) = loop(l - 1, bits');
          Ok(([ext, ...tail], payload));
        };
      };
      let* (list, payload) = loop(Int32.to_int(length), payload);
      Ok((TList(list), payload));
    }
  | {| _ |} => Error(`CannotDecode)

and decode_compound = bits => {
  let rec loop = payload => {
    let* ({tag, value}, bits') = decode_payload(payload);
    switch (value) {
    | TNothing => Ok(([], bits'))
    | _ =>
      let* (tail, bits') = loop(bits');
      Ok(([{tag, value}, ...tail], bits'));
    };
  };
  let* (list, payload) = loop(bits);
  Ok((TCompound(list), payload));
}

and decode_payload = bits => {
  let* (id, name, bits') = decode_tag(bits);
  switch (id) {
  | 0 => Ok(({tag: "", value: TNothing}, bits'))
  | id =>
    let* (value, bits') = decode_ext_nbt(bits', id);
    Ok(({tag: name, value}, bits'));
  };
}

and decode_ext_nbt = payload =>
  fun
  | 0 => Ok((TNothing, payload))
  | 1 => decode_byte(payload)
  | 2 => decode_short(payload)
  | 3 => decode_int(payload)
  | 4 => decode_long(payload)
  | 5 => decode_float(payload)
  | 6 => decode_double(payload)
  | 7 => decode_byte_array(payload)
  | 8 => decode_string(payload)
  | 9 => decode_list(payload)
  | 10 => decode_compound(payload)
  | _ => Error(`CannotDecode);
