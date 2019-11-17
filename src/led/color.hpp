namespace TableDisco
{
    struct Color
    {
        unsigned char Red;
        unsigned char Green;
        unsigned char Blue;

        bool isBlack() { return Red == 0 && Green == 0 && Blue == 0; }
        bool operator!=(const Color other) { return other.Red != Red || other.Green != Green || other.Blue != Blue; }
    };

    static const Color Black = { 0, 0, 0 };
    static const Color Red = { 255, 0, 0 };
    static const Color Green = { 0, 255, 0 };
    static const Color Blue = { 0, 0, 255 };
    static const Color Yellow = { 255, 255, 0 };
    static const Color Ivory = { 255, 255, 240 };
    static const Color Cyan = { 0, 255, 255 };
}