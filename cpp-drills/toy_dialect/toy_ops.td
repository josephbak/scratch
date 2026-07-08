#ifndef TOY_OPS
#define TOY_OPS

include "mlir/IR/OpBase.td"

// ── SLOT 1: the dialect ──────────────────────────────
def Toy_Dialect : Dialect {
  let name = "toy";
  let cppNamespace = "::toy";
}

// ── op base: binds every op in this dialect to the dialect above ──
class Toy_Op<string mnemonic, list<Trait> traits = []>
    : Op<Toy_Dialect, mnemonic, traits>;

// ── SLOT 2–4: the op ─────────────────────────────────
def Toy_IdentityOp : Toy_Op<"identity", [/* traits, can be empty */]> {
  let summary = "identity op: returns its input unchanged";

  let arguments = (ins AnyType:$input);
  let results   = (outs AnyType:$output);
}

#endif // TOY_OPS