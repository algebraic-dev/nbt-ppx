let read_file = path => {
  let ic = open_in(path);
  really_input_string(ic, in_channel_length(ic));
};

let print_nbt_result = result => {
  switch (result) {
  | Ok((tag, _)) => print_endline("OK: " ++ Lib.Data.show_tag(tag))
  | Error(_) => print_endline("ERROR")
  };
};

let%expect_test "uncompressed.nbt" = {
  let content = read_file("../test_suite/uncompressed.nbt");
  let result = Lib.Decode.decode_uncompressed(content);
  print_nbt_result(result);
  %expect
  {|
    OK: { tag = "hello world";
      value = (TCompound [{ tag = "name"; value = (TString "Bananrama") }]) }  |};
};

let%expect_test "gzipped.nbt" = {
  let content = read_file("../test_suite/gzipped.nbt");
  let result = Lib.Decode.decode_zipped(content);
  print_nbt_result(result);
  %expect
  {|
    OK: { tag = "Level";
      value =
      (TCompound
         [{ tag = "longTest"; value = (TLong 9223372036854775807L) };
           { tag = "shortTest"; value = (TShort 32767) };
           { tag = "stringTest";
             value =
             (TString
                "HELLO WORLD THIS IS A TEST STRING \195\133\195\132\195\150!")
             };
           { tag = "floatTest"; value = (TFloat 0.498231470585) };
           { tag = "intTest"; value = (TInt 2147483647l) };
           { tag = "nested compound test";
             value =
             (TCompound
                [{ tag = "ham";
                   value =
                   (TCompound
                      [{ tag = "name"; value = (TString "Hampus") };
                        { tag = "value"; value = (TFloat 0.75) }])
                   };
                  { tag = "egg";
                    value =
                    (TCompound
                       [{ tag = "name"; value = (TString "Eggbert") };
                         { tag = "value"; value = (TFloat 0.5) }])
                    }
                  ])
             };
           { tag = "listTest (long)";
             value =
             (TList
                [(TLong 11L); (TLong 12L); (TLong 13L); (TLong 14L); (TLong 15L)])
             };
           { tag = "listTest (compound)";
             value =
             (TList
                [(TCompound
                    [{ tag = "name"; value = (TString "Compound tag #0") };
                      { tag = "created-on"; value = (TLong 1264099775885L) }]);
                  (TCompound
                     [{ tag = "name"; value = (TString "Compound tag #1") };
                       { tag = "created-on"; value = (TLong 1264099775885L) }])
                  ])
             };
           { tag = "byteTest"; value = (TByte 127) };
           { tag =
             "byteArrayTest (the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...))";
             value =
             (TByteArray
                "\000>\"\016\b\n\022,L\018F \004VNP\\\014.X(\002J802>T\016:\nH,\026\018\020 6V\028P*\014`XZ\002\0248b2\012TB:<H^\026D\020R6$\028\030*@`&Z4\024\006b\000\012\"B\b<\022^LDFR\004$N\030\\@.&(4J\0060\000>\"\016\b\n\022,L\018F \004VNP\\\014.X(\002J802>T\016:\nH,\026\018\020 6V\028P*\014`XZ\002\0248b2\012TB:<H^\026D\020R6$\028\030*@`&Z4\024\006b\000\012\"B\b<\022^LDFR\004$N\030\\@.&(4J\0060\000>\"\016\b\n\022,L\018F \004VNP\\\014.X(\002J802>T\016:\nH,\026\018\020 6V\028P*\014`XZ\002\0248b2\012TB:<H^\026D\020R6$\028\030*@`&Z4\024\006b\000\012\"B\b<\022^LDFR\004$N\030\\@.&(4J\0060\000>\"\016\b\n\022,L\018F \004VNP\\\014.X(\002J802>T\016:\nH,\026\018\020 6V\028P*\014`XZ\002\0248b2\012TB:<H^\026D\020R6$\028\030*@`&Z4\024\006b\000\012\"B\b<\022^LDFR\004$N\030\\@.&(4J\0060\000>\"\016\b\n\022,L\018F \004VNP\\\014.X(\002J802>T\016:\nH,\026\018\020 6V\028P*\014`XZ\002\0248b2\012TB:<H^\026D\020R6$\028\030*@`&Z4\024\006b\000\012\"B\b<\022^LDFR\004$N\030\\@.&(4J\0060\000>\"\016\b\n\022,L\018F \004VNP\\\014.X(\002J802>T\016:\nH,\026\018\020 6V\028P*\014`XZ\002\0248b2\012TB:<H^\026D\020R6$\028\030*@`&Z4\024\006b\000\012\"B\b<\022^LDFR\004$N\030\\@.&(4J\0060\000>\"\016\b\n\022,L\018F \004VNP\\\014.X(\002J802>T\016:\nH,\026\018\020 6V\028P*\014`XZ\002\0248b2\012TB:<H^\026D\020R6$\028\030*@`&Z4\024\006b\000\012\"B\b<\022^LDFR\004$N\030\\@.&(4J\0060\000>\"\016\b\n\022,L\018F \004VNP\\\014.X(\002J802>T\016:\nH,\026\018\020 6V\028P*\014`XZ\002\0248b2\012TB:<H^\026D\020R6$\028\030*@`&Z4\024\006b\000\012\"B\b<\022^LDFR\004$N\030\\@.&(4J\0060\000>\"\016\b\n\022,L\018F \004VNP\\\014.X(\002J802>T\016:\nH,\026\018\020 6V\028P*\014`XZ\002\0248b2\012TB:<H^\026D\020R6$\028\030*@`&Z4\024\006b\000\012\"B\b<\022^LDFR\004$N\030\\@.&(4J\0060\000>\"\016\b\n\022,L\018F \004VNP\\\014.X(\002J802>T\016:\nH,\026\018\020 6V\028P*\014`XZ\002\0248b2\012TB:<H^\026D\020R6$\028\030*@`&Z4\024\006b\000\012\"B\b<\022^LDFR\004$N\030\\@.&(4J\0060")
             };
           { tag = "doubleTest"; value = (TDouble 0.493128713218) }])
      }  |};
};

let%expect_test "gzipped.nbt" = {
  let content = read_file("../test_suite/gzipped.nbt");
  let result = Lib.Decode.decode_zipped(content);
  (
    switch (result) {
    | Ok((tag, _)) =>
      let encode = Lib.Encode.encode(tag);
      switch (encode) {
      | Ok(encoded) =>
        switch (Ezgzip.decompress(content)) {
        | Ok(decompressed) =>
          encoded == decompressed
            ? "EQUAL"
            : Printf.sprintf(
                "NOT EQUAL: size: %dx%d",
                String.length(encoded),
                String.length(decompressed),
              )
        | Error(_) => "Error while decompressing"
        }
      | Error(_) => "Error on encoding"
      };
    | Error(_) => "Error on decoding"
    }
  )
  |> print_endline;
  %expect
  {| |};
};
