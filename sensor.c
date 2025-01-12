#include <stdio.h>
#include <stdint.h>

// G range için enum
typedef enum {
    G_2 = 0b000,  // ±2g
    G_4 = 0b001,  // ±4g
    G_8 = 0b010,  // ±8g
    G_16 = 0b011  // ±16g
} GRange;

// Bandwidth için enum
typedef enum {
    BW_7_81 = 0b000,  // 7.81 Hz
    BW_15_63 = 0b001, // 15.63 Hz
    BW_31_25 = 0b010, // 31.25 Hz
    BW_62_5 = 0b011,  // 62.5 Hz
    BW_125 = 0b100,   // 125 Hz
    BW_250 = 0b101,   // 250 Hz
    BW_500 = 0b110,   // 500 Hz
    BW_1000 = 0b111   // 1000 Hz
} Bandwidth;

// Operation mode için enum
typedef enum {
    MODE_NORMAL = 0b00,   // Normal mode
    MODE_SUSPEND = 0b01,  // Suspend mode
    MODE_LOW_POWER = 0b10 // Low power mode
} OperationMode;

// Konfigürasyon struct'ı
typedef struct {
    GRange g_range;
    Bandwidth bandwidth;
    OperationMode op_mode;
    uint8_t AccConfigValue; // Hesaplanan değer
} AccConfig;

// AccConfigValue hesaplama fonksiyonu
uint8_t calculateAccConfigValue(GRange g, Bandwidth bw, OperationMode op) {
    return (g << 5) | (bw << 2) | op; // Bitwise operatörleriyle hesaplama
}

int main() {
    // Konfigürasyon değerlerini struct içinde tanımlama
    AccConfig config;
    config.g_range = G_4;            // ±4g
    config.bandwidth = BW_125;       // 125 Hz
    config.op_mode = MODE_NORMAL;    // Normal mode

    // AccConfigValue hesaplama
    config.AccConfigValue = calculateAccConfigValue(config.g_range, config.bandwidth, config.op_mode);

    // Sonuçları yazdırma
    printf("AccConfigValue Decimal: %d\n", config.AccConfigValue);
    printf("AccConfigValue Hexadecimal: 0x%X\n", config.AccConfigValue);
    printf("AccConfigValue Binary: 0b");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (config.AccConfigValue >> i) & 1);
    }
    printf("\n");

    return 0;
}
