#include <stdio.h>
#include <string.h>

int main() {
    // Hang so va khai bao mang song song
    const int MAX_PHIEU = 50;
    char maPhieu[50][20];
    int ngayQuaHan[50];

    // Khoi tao 3 du lieu mau
    // Phieu 1: PM101 - 0 ngay
    strcpy(maPhieu[0], "PM101");
    ngayQuaHan[0] = 0;

    // Phieu 2: PM102 - 3 ngay
    strcpy(maPhieu[1], "PM102");
    ngayQuaHan[1] = 3;

    // Phieu 3: PM103 - 5 ngay
    strcpy(maPhieu[2], "PM103");
    ngayQuaHan[2] = 5;

    int soLuong = 3; // Bien dem so luong phieu hien tai
    int chon = 0;

    do {
        printf("\n--- HE THONG QUAN LY MUON TRA SACH (LIBRARY_WMS) ---\n");
        printf("1. Xem danh sach phieu muon\n");
        printf("2. Them moi phieu muon\n");
        printf("3. Cap nhat so ngay qua han\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &chon);

        // Lam sach bo dem ban phim sau khi scan so
        while (getchar() != '\n');

        switch (chon) {
            case 1: { // 1. XEM DANH SACH PHIEU MUON
                printf("\n--- DANH SACH PHIEU MUON SACH ---\n");
                printf("STT | Ma Phieu | So Ngay Qua Han | Tien Phat (VND)\n");
                printf("--------------------------------------------------\n");

                if (soLuong == 0) {
                    printf("Danh sach hien tai dang rong!\n");
                } else {
                    for (int i = 0; i < soLuong; i++) {
                        long tienPhat = (long)ngayQuaHan[i] * 5000;
                        printf("%d | %s | %d ngay | %ld VND\n", 
                               i + 1, maPhieu[i], ngayQuaHan[i], tienPhat);
                    }
                }

                printf("--------------------------------------------------\n");
                printf("Tong so phieu: %d\n", soLuong);
                break;
            }

            case 2: { // 2. THEM MOI PHIEU MUON
                if (soLuong >= MAX_PHIEU) {
                    printf("Loi: Danh sach phieu muon da day, khong the them!\n");
                    break;
                }

                printf("\nNhap ma phieu muon moi: ");
                fgets(maPhieu[soLuong], sizeof(maPhieu[soLuong]), stdin);
                // Xoa ky tu '\n' do fgets() luu lai
                maPhieu[soLuong][strcspn(maPhieu[soLuong], "\n")] = '\0';

                // Mac dinh so ngay qua han ban dau = 0
                ngayQuaHan[soLuong] = 0;

                soLuong++; // Tang so luong phieu
                printf("Them phieu muon thanh cong!\n");
                break;
            }

            case 3: { // 3. CAP NHAT SO NGAY QUA HAN
                if (soLuong == 0) {
                    printf("Danh sach phieu muon dang rong!\n");
                    break;
                }

                char timMa[20];
                printf("\nNhap ma phieu muon can cap nhat: ");
                fgets(timMa, sizeof(timMa), stdin);
                timMa[strcspn(timMa, "\n")] = '\0';

                int viTri = -1;
                // Tim kiem tuyen tinh bang strcmp()
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], timMa) == 0) {
                        viTri = i;
                        break;
                    }
                }

                if (viTri == -1) {
                    printf("Khong tim thay phieu muon '%s' trong he thong!\n", timMa);
                } else {
                    printf("Tim thay phieu muon '%s' tai vi tri index %d.\n", timMa, viTri);
                    
                    int soNgayMoi = -1;
                    do {
                        printf("Nhap so ngay qua han moi: ");
                        scanf("%d", &soNgayMoi);
                        
                        // Lam sach bo dem ban phim
                        while (getchar() != '\n');

                        if (soNgayMoi < 0) {
                            printf("Loi: So ngay qua han phai la so nguyen khong am (>= 0)! Vui long nhap lai.\n");
                        }
                    } while (soNgayMoi < 0);

                    // Ghi de so ngay qua han moi vao mang
                    ngayQuaHan[viTri] = soNgayMoi;
                    printf("Cap nhat thanh cong! So ngay qua han moi cua %s la %d ngay.\n", 
                           maPhieu[viTri], ngayQuaHan[viTri]);
                }
                break;
            }

            case 0:
                printf("\nCam on ban da su dung HE THONG QUAN LY MUON TRA SACH (LIBRARY_WMS)!\n");
                break;

            default:
                printf("Lua chon khong hop le! Vui long chon cac chuc nang tu 0 den 3.\n");
                break;
        }

    } while (chon != 0);

    return 0;
}