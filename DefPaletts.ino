CHSVPalette16 SetupGoldenPeachPalette()
{
    CHSV peach  = CHSV(41, 204, 255);
    CHSV yellow = CHSV(63, 224, 255);
    CHSV black  = CHSV(0,0,0);
    
    return CHSVPalette16(
      peach,
      yellow,
      yellow,
      peach);
}

CHSVPalette16 SetupRoyalPurplePalette()
{
    CHSV teal  = CHSV(144, 204, 255);
    CHSV blue  = CHSV(180, 204, 255);
    CHSV purple = CHSV(210, 224, 255);
    CHSV black  = CHSV(0,0,0);
    
    return CHSVPalette16(
      teal,
      purple,
      purple,
      teal);
}

CHSVPalette16 SetupPurpleAndGreenPalette()
{
    CHSV purple = CHSV( HUE_PURPLE, 255, 255);
    CHSV green  = CHSV( HUE_GREEN, 255, 255);
    CHSV black  = CHSV(0,0,0);
    
    return CHSVPalette16(
      green,  green,  black,  black,
      purple, purple, black,  black,
      green,  green,  black,  black,
      purple, purple, black,  black );
}

CHSVPalette16 SetupBlueAndWhitePalette()
{
    CHSV blue = CHSV( HUE_BLUE, 255, 255);
    CHSV white  = CHSV(0,0,255);
    CHSV black  = CHSV(0,0,0);
    
    return CHSVPalette16(
      blue, blue, white,  white,
      blue, blue, white,  white,
      blue, blue, white,  white,
      blue, blue, white,  white );
}

CHSVPalette16 CustomPalette()
{
    CHSV c1 = CHSV(hue1, 255, 255);
    CHSV c2  = CHSV(hue2, 255, 255);
    CHSV black  = CHSV(0,0,0);
    
    return CHSVPalette16(
      c1,
      c2,
      c2,
      c1);
}
