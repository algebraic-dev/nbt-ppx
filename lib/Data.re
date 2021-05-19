type i8;
type i16;
type i32;
type i64;
type double;

[@deriving show({with_path: false})]
type tag = {
  tag: string,
  value: nbt,
}

and nbt =
  | TNothing
  | TByte(int)
  | TShort(int)
  | TInt(int32)
  | TLong(int64)
  | TFloat(float)
  | TDouble(float)
  | TByteArray(string)
  | TString(string)
  | TList(list(nbt))
  | TCompound(list(tag))
  | TIntArray(list(int))
  | TLongArray(list(int));
