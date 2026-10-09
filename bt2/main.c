#include <stdio.h>
#include <string.h>

int main() {
    // Hang so va khai bao mang song song
    const int MAX = 100;
    char maPhieu[100][15];
    char tenSach[100][50];
    int soNgayMuon[100];
    int tienPhat[100];

    int soLuong = 0; // Bien dem so luong phieu muon hien tai
    int chon = 0;

    do {
        printf("\n================ HET HONG QUAN LY MUON TRA SACH (LIBRARY_WMS) ================\n");
        printf("1. Them luot muon sach moi\n");
        printf("2. Hien thi danh sach muon sach\n");
        printf("3. Cap nhat so ngay muon theo Ma phieu\n");
        printf("4. Xoa luot muon sach theo Ma phieu\n");
        printf("5. Thong ke danh sach phieu muon bi phat (Qua han > 14 ngay)\n");
        printf("6. Thoat chuong trinh\n");
        printf("==============================================================================\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &chon);

        // Lam sach bo dem ban phim sau khi scan so
        while (getchar() != '\n');

        switch (chon) {
            case 1: { // 1. THEM LUOT MUON SACH MOI
                printf("\n=== THEM LUOT MUON SACH MOI ===\n");
                
                if (soLuong >= MAX) {
                    printf("He thong day, khong the them phieu muon moi!\n");
                    break;
                }

                // Nhap va kiem tra trung lap Ma phieu
                char maNhap[15];
                int biTrung = 0;
                do {
                    biTrung = 0;
                    printf("Nhap ma phieu muon: ");
                    fgets(maNhap, sizeof(maNhap), stdin);
                    maNhap[strcspn(maNhap, "\n")] = '\0'; // Xoa ký tu '\n'

                    // Kiem tra chuoi rong
                    if (strlen(maNhap) == 0) {
                        printf("Ma phieu khong duoc de rong! Vui long nhap lai.\n");
                        biTrung = 1;
                        continue;
                    }

                    // Tim kiem tuyen tinh kiem tra trùng lap
                    for (int i = 0; i < soLuong; i++) {
                        if (strcmp(maPhieu[i], maNhap) == 0) {
                            printf("Loi: Ma phieu '%s' da ton tai trong he thong! Vui long nhap ma khac.\n", maNhap);
                            biTrung = 1;
                            break;
                        }
                    }
                } while (biTrung);

                // Luu ma phieu hop le vao mang
                strcpy(maPhieu[soLuong], maNhap);

                // Nhap Ten sach
                printf("Nhap ten sach: ");
                fgets(tenSach[soLuong], sizeof(tenSach[soLuong]), stdin);
                tenSach[soLuong][strcspn(tenSach[soLuong], "\n")] = '\0';

                // Nhap So ngay muon (nguyen duong > 0)
                int ngay = 0;
                do {
                    printf("Nhap so ngay muon thuc te: ");
                    scanf("%d", &ngay);
                    while (getchar() != '\n'); // Lam sach bo dem

                    if (ngay <= 0) {
                        printf("Loi: So ngay muon phai la so nguyen lon hon 0! Vui long nhap lai.\n");
                    }
                } while (ngay <= 0);

                soNgayMuon[soLuong] = ngay;

                // Tinh tien phat: (soNgayMuon > 14) ? (soNgayMuon - 14) * 5000 : 0
                tienPhat[soLuong] = (soNgayMuon[soLuong] > 14) ? (soNgayMuon[soLuong] - 14) * 5000 : 0;

                printf("\n--> Tien phat tu dong tinh: %d VND\n", tienPhat[soLuong]);
                soLuong++; // Tang so luong phieu
                printf("--> Them luot muon sach thanh cong!\n");
                break;
            }

            case 2: { // 2. HIEN THI DANH SACH MUON SACH
                printf("\n================================ DANH SACH MUON SACH ================================\n");
                if (soLuong == 0) {
                    printf("Danh sach muon sach hien dang rong!\n");
                } else {
                    printf("%-5s | %-12s | %-35s | %-10s | %-15s\n", 
                           "STT", "Ma Phieu", "Ten Sach", "So Ngay", "Tien Phat (VND)");
                    printf("-------------------------------------------------------------------------------------\n");

                    long tongTienPhat = 0;
                    for (int i = 0; i < soLuong; i++) {
                        printf("%-5d | %-12s | %-35s | %-10d | %-15d\n", 
                               i + 1, maPhieu[i], tenSach[i], soNgayMuon[i], tienPhat[i]);
                        tongTienPhat += tienPhat[i];
                    }
                    printf("-------------------------------------------------------------------------------------\n");
                    printf("Tong tien phat toan he thong: %ld VND\n", tongTienPhat);
                }
                break;
            }

            case 3: { // 3. CAP NHAT SO NGAY MUON THEO MA PHIEU
                printf("\n=== CAP NHAT SO NGAY MUON ===\n");
                if (soLuong == 0) {
                    printf("Danh sach phieu muon dang rong!\n");
                    break;
                }

                char timMa[15];
                printf("Nhap ma phieu muon can cap nhat: ");
                fgets(timMa, sizeof(timMa), stdin);
                timMa[strcspn(timMa, "\n")] = '\0';

                int viTri = -1;
                // Tim kiem tuyen tinh
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], timMa) == 0) {
                        viTri = i;
                        break;
                    }
                }

                if (viTri == -1) {
                    printf("Khong tim thay phieu muon co ma: %s\n", timMa);
                } else {
                    printf("Tim thay phieu muon cua sach: %s (So ngay hien tai: %d)\n", 
                           tenSach[viTri], soNgayMuon[viTri]);

                    int ngayMoi = 0;
                    do {
                        printf("Nhap so ngay muon thuc te moi: ");
                        scanf("%d", &ngayMoi);
                        while (getchar() != '\n'); // Lam sach bo dem

                        if (ngayMoi <= 0) {
                            printf("Loi: So ngay muon phai la so nguyen lon hon 0! Vui long nhap lai.\n");
                        }
                    } while (ngayMoi <= 0);

                    // Cap nhat va tinh lai tien phat
                    soNgayMuon[viTri] = ngayMoi;
                    tienPhat[viTri] = (soNgayMuon[viTri] > 14) ? (soNgayMuon[viTri] - 14) * 5000 : 0;

                    printf("\n--> Tien phat moi: %d VND\n", tienPhat[viTri]);
                    printf("--> Cap nhat so ngay muon thanh cong!\n");
                }
                break;
            }

            case 4: { // 4. XOA LUOT MUON SACH THEO MA PHIEU
                printf("\n=== XOA LUOT MUON SACH ===\n");
                if (soLuong == 0) {
                    printf("Danh sach phieu muon dang rong!\n");
                    break;
                }

                char timMa[15];
                printf("Nhap ma phieu muon can xoa: ");
                fgets(timMa, sizeof(timMa), stdin);
                timMa[strcspn(timMa, "\n")] = '\0';

                int viTri = -1;
                // Tim kiem tuyen tinh
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], timMa) == 0) {
                        viTri = i;
                        break;
                    }
                }

                if (viTri == -1) {
                    printf("Khong tim thay phieu muon co ma: %s\n", timMa);
                } else {
                    // Thuat toan don mang tu vi tri index den soLuong - 2
                    for (int i = viTri; i < soLuong - 1; i++) {
                        strcpy(maPhieu[i], maPhieu[i + 1]);
                        strcpy(tenSach[i], tenSach[i + 1]);
                        soNgayMuon[i] = soNgayMuon[i + 1];
                        tienPhat[i] = tienPhat[i + 1];
                    }

                    soLuong--; // Giam so luong
                    printf("--> Xoa phieu muon thanh cong!\n");
                }
                break;
            }

            case 5: { // 5. THONG KE PHIEU MUON QUÁ HẠN (> 14 NGÀY)
                printf("\n=================== DANH SACH PHIEU MUON QUA HAN (> 14 NGAY) ===================\n");
                if (soLuong == 0) {
                    printf("Danh sach phieu muon dang rong!\n");
                    break;
                }

                int demQuaHan = 0;
                printf("%-5s | %-12s | %-35s | %-10s | %-15s\n", 
                       "STT", "Ma Phieu", "Ten Sach", "So Ngay", "Tien Phat (VND)");
                printf("-------------------------------------------------------------------------------------\n");

                for (int i = 0; i < soLuong; i++) {
                    if (soNgayMuon[i] > 14) {
                        demQuaHan++;
                        printf("%-5d | %-12s | %-35s | %-10d | %-15d\n", 
                               demQuaHan, maPhieu[i], tenSach[i], soNgayMuon[i], tienPhat[i]);
                    }
                }

                if (demQuaHan == 0) {
                    printf("Khong co luot muon nao bi qua han phat!\n");
                }
                printf("-------------------------------------------------------------------------------------\n");
                printf("Tong so phieu qua han: %d\n", demQuaHan);
                break;
            }

            case 6:
                printf("\nThoat chuong trinh. Cam on ban da su dung HE THONG QUAN LY MUON TRA SACH (LIBRARY_WMS)!\n");
                break;

            default:
                printf("Lua chon khong hop le. Vui long thu lai!\n");
                break;
        }

    } while (chon != 6);

    return 0;
}