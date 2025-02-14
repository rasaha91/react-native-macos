/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// TODO(macOS GH#774)

#import <React/RCTDynamicTypeRamp.h>

@implementation RCTConvert (DynamicTypeRamp)

RCT_ENUM_CONVERTER(RCTDynamicTypeRamp, (@{
  @"caption2": @(RCTDynamicTypeRampCaption2),
  @"caption1": @(RCTDynamicTypeRampCaption1),
  @"footnote": @(RCTDynamicTypeRampFootnote),
  @"subhead": @(RCTDynamicTypeRampSubhead),
  @"callout": @(RCTDynamicTypeRampCallout),
  @"body": @(RCTDynamicTypeRampBody),
  @"headline": @(RCTDynamicTypeRampHeadline),
  @"title3": @(RCTDynamicTypeRampTitle3),
  @"title2": @(RCTDynamicTypeRampTitle2),
  @"title1": @(RCTDynamicTypeRampTitle1),
  @"largeTitle": @(RCTDynamicTypeRampLargeTitle),
}), RCTDynamicTypeRampUndefined, integerValue)

@end

#if !TARGET_OS_OSX // [TODO(macOS GH#774)
UIFontMetrics *RCTUIFontMetricsForDynamicTypeRamp(RCTDynamicTypeRamp dynamicTypeRamp) {
  static NSDictionary<NSNumber *, UIFontTextStyle> *mapping;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    mapping = @{
      @(RCTDynamicTypeRampCaption2): UIFontTextStyleCaption2,
      @(RCTDynamicTypeRampCaption1): UIFontTextStyleCaption1,
      @(RCTDynamicTypeRampFootnote): UIFontTextStyleFootnote,
      @(RCTDynamicTypeRampSubhead): UIFontTextStyleSubheadline,
      @(RCTDynamicTypeRampCallout): UIFontTextStyleCallout,
      @(RCTDynamicTypeRampBody): UIFontTextStyleBody,
      @(RCTDynamicTypeRampHeadline): UIFontTextStyleHeadline,
      @(RCTDynamicTypeRampTitle3): UIFontTextStyleTitle3,
      @(RCTDynamicTypeRampTitle2): UIFontTextStyleTitle2,
      @(RCTDynamicTypeRampTitle1): UIFontTextStyleTitle1,
      @(RCTDynamicTypeRampLargeTitle): UIFontTextStyleLargeTitle,
    };
  });

  id textStyle = mapping[@(dynamicTypeRamp)] ?: UIFontTextStyleBody; // Default to body if we don't recognize the specified ramp
  return [UIFontMetrics metricsForTextStyle:textStyle];
}

CGFloat RCTUIBaseSizeForDynamicTypeRamp(RCTDynamicTypeRamp dynamicTypeRamp) {
  static NSDictionary<NSNumber *, NSNumber *> *mapping;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    // Values taken from https://developer.apple.com/design/human-interface-guidelines/foundations/typography/
    mapping = @{
      @(RCTDynamicTypeRampCaption2): @11,
      @(RCTDynamicTypeRampCaption1): @12,
      @(RCTDynamicTypeRampFootnote): @13,
      @(RCTDynamicTypeRampSubhead): @15,
      @(RCTDynamicTypeRampCallout): @16,
      @(RCTDynamicTypeRampBody): @17,
      @(RCTDynamicTypeRampHeadline): @17,
      @(RCTDynamicTypeRampTitle3): @20,
      @(RCTDynamicTypeRampTitle2): @22,
      @(RCTDynamicTypeRampTitle1): @28,
      @(RCTDynamicTypeRampLargeTitle): @34,
    };
  });

  NSNumber *baseSize = mapping[@(dynamicTypeRamp)] ?: @17; // Default to body size if we don't recognize the specified ramp
  return CGFLOAT_IS_DOUBLE ? [baseSize doubleValue] : [baseSize floatValue];
}
#endif // ]TODO(macOS GH#774)
