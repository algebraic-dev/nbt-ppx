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
  | TIntArray(list(int32))
  | TLongArray(list(int64));
