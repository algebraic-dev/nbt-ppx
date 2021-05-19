open Data;
open Buffer;

let rec encode_tag = (buffer, tag) => {
  let id = get_id(tag.value);
  Buffer.add_uint8(buffer, id);
  Buffer.add_uint16_be(buffer, String.length(tag.tag));
  Buffer.add_string(buffer, tag.tag);
  encode_tree(buffer, tag.value);
}

and get_id =
  fun
  | TNothing => 0
  | TByte(_) => 1
  | TShort(_) => 2
  | TInt(_) => 3
  | TLong(_) => 4
  | TFloat(_) => 5
  | TDouble(_) => 6
  | TByteArray(_) => 7
  | TString(_) => 8
  | TList(_) => 9
  | TCompound(_) => 10
  | TIntArray(_) => 11
  | TLongArray(_) => 12

and encode_tree = buffer =>
  fun
  | TNothing => add_int8(buffer, 0)
  | TByte(byte) => add_int8(buffer, byte)
  | TShort(word) => add_int16_be(buffer, word)
  | TInt(dword) => add_int32_be(buffer, dword)
  | TLong(qword) => add_int64_be(buffer, qword)
  | TFloat(float) => add_int32_be(buffer, Int32.bits_of_float(float))
  | TDouble(float) => add_int64_be(buffer, Int64.bits_of_float(float))
  | TByteArray(string) => {
      Buffer.add_int32_be(buffer, String.length(string) |> Int32.of_int);
      add_string(buffer, string);
    }
  | TString(string) => {
      Buffer.add_uint16_be(buffer, String.length(string));
      add_string(buffer, string);
    }
  | TList(ls) => {
      switch (ls) {
      | [hd, ..._] => Buffer.add_uint8(buffer, get_id(hd))
      | _ => Buffer.add_uint8(buffer, 0)
      };
      Buffer.add_int32_be(buffer, List.length(ls) |> Int32.of_int);
      List.iter(encode_tree(buffer), ls);
    }
  | TCompound(ls) => {
      List.iter(encode_tag(buffer), ls);
      Buffer.add_int8(buffer, 0);
    }
  | TIntArray(ls) => {
      Buffer.add_int32_be(buffer, List.length(ls) |> Int32.of_int);
      List.iter(n => Buffer.add_int32_be(buffer, n), ls);
    }
  | TLongArray(ls) => {
      Buffer.add_int32_be(buffer, List.length(ls) |> Int32.of_int);
      List.iter(n => Buffer.add_int64_be(buffer, n), ls);
    };

let encode = tree => {
  let buffer = create(100);
  encode_tag(buffer, tree);
  Ok(contents(buffer));
};
