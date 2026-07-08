// ToyPatterns.h
#ifndef TOY_PATTERNS_H
#define TOY_PATTERNS_H

namespace mlir { class RewritePatternSet; }

void populateToyPatterns(mlir::RewritePatternSet &patterns);

#endif // TOY_PATTERNS_H