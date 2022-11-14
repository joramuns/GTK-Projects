#include "utils.h"

GdkRGBA*
get_rgba_settings_prop (GSettings *settings,
                        const char *prop)
{
  GVariant *value = g_settings_get_value (settings, prop);
  double *array = (double*) g_variant_get_data (value); 
  GdkRGBA *rgba = g_malloc(sizeof(GdkRGBA));
  rgba->red = array[0];
  rgba->green = array[1];
  rgba->blue = array[2];
  rgba->alpha = array[3];
  return rgba;
}

void
set_rgba_settings_prop (GSettings *settings,
                        const char *prop,
                        GdkRGBA* rgba)
{
  double values[] = { 
    rgba->red,
    rgba->green,
    rgba->blue,
    rgba->alpha,
  };
  GVariantType *value_type = g_variant_type_new ("(dddd)");
  GVariant *value = g_variant_new_from_data (value_type, values,
                                             sizeof(values), TRUE,
                                             NULL, NULL);
  g_settings_set_value(settings, prop, value);
  g_variant_type_free (value_type);
}

