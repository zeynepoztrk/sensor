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
    AccConfig config;

    int g_range_input, bandwidth_input, op_mode_input;

    // Kullanıcıdan G range'i isteme
    printf("G Range Seciniz (0: ±2g, 1: ±4g, 2: ±8g, 3: ±16g): ");
    scanf("%d", &g_range_input);
    if (g_range_input < 0 || g_range_input > 3) {
        printf("Hatali G Range secimi!\n");
        return 1;
    }
    config.g_range = (GRange)g_range_input;

    // Kullanıcıdan Bandwidth isteme
    printf("Bandwidth Seciniz (0: 7.81 Hz, 1: 15.63 Hz, 2: 31.25 Hz, 3: 62.5 Hz, 4: 125 Hz, 5: 250 Hz, 6: 500 Hz, 7: 1000 Hz): ");
    scanf("%d", &bandwidth_input);
    if (bandwidth_input < 0 || bandwidth_input > 7) {
        printf("Hatali Bandwidth secimi!\n");
        return 1;
    }
    config.bandwidth = (Bandwidth)bandwidth_input;

    // Kullanıcıdan Operation Mode isteme
    printf("Operation Mode Seciniz (0: Normal, 1: Suspend, 2: Low Power): ");
    scanf("%d", &op_mode_input);
    if (op_mode_input < 0 || op_mode_input > 2) {
        printf("Hatali Operation Mode secimi!\n");
        return 1;
    }
    config.op_mode = (OperationMode)op_mode_input;

    // AccConfigValue hesaplama
    config.AccConfigValue = calculateAccConfigValue(config.g_range, config.bandwidth, config.op_mode);

    // Sonuçları yazdırma
    printf("\nSecilen Ayarlar:\n");
    printf("G Range: %d\n", g_range_input);
    printf("Bandwidth: %d\n", bandwidth_input);
    printf("Operation Mode: %d\n", op_mode_input);

    printf("\nHesaplanan AccConfigValue:\n");
    printf("Decimal: %d\n", config.AccConfigValue);
    printf("Hexadecimal: 0x%X\n", config.AccConfigValue);
    printf("Binary: 0b");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (config.AccConfigValue >> i) & 1);
    }
    printf("\n");

    return 0;
}