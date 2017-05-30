/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.microsoft.adaptivecards.objectmodel;

public class TextOptions {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected TextOptions(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(TextOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        AdaptiveCardObjectModelJNI.delete_TextOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setWeight(TextWeight value) {
    AdaptiveCardObjectModelJNI.TextOptions_weight_set(swigCPtr, this, value.swigValue());
  }

  public TextWeight getWeight() {
    return TextWeight.swigToEnum(AdaptiveCardObjectModelJNI.TextOptions_weight_get(swigCPtr, this));
  }

  public void setSize(TextSize value) {
    AdaptiveCardObjectModelJNI.TextOptions_size_set(swigCPtr, this, value.swigValue());
  }

  public TextSize getSize() {
    return TextSize.swigToEnum(AdaptiveCardObjectModelJNI.TextOptions_size_get(swigCPtr, this));
  }

  public void setColor(TextColor value) {
    AdaptiveCardObjectModelJNI.TextOptions_color_set(swigCPtr, this, value.swigValue());
  }

  public TextColor getColor() {
    return TextColor.swigToEnum(AdaptiveCardObjectModelJNI.TextOptions_color_get(swigCPtr, this));
  }

  public void setIsSubtle(boolean value) {
    AdaptiveCardObjectModelJNI.TextOptions_isSubtle_set(swigCPtr, this, value);
  }

  public boolean getIsSubtle() {
    return AdaptiveCardObjectModelJNI.TextOptions_isSubtle_get(swigCPtr, this);
  }

  public TextOptions() {
    this(AdaptiveCardObjectModelJNI.new_TextOptions(), true);
  }

}