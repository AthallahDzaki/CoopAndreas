#pragma once
class CNetworkVehicle
{
public:
	int m_nVehicleId = -1;
	CVehicle* m_pVehicle = nullptr;
	int m_nModelId;
	char m_nPaintJob = -1;
	float m_fAimHorizontal;
	float m_fAimVertical;
	CNetworkVehicle(CVehicle* vehicle);
	CNetworkVehicle(int vehicleid, int modelid, CVector pos, float rotation, unsigned char color1, unsigned char color2);
	bool CreateVehicle(int vehicleid, int modelid, CVector pos, float rotation, unsigned char color1, unsigned char color2);
	~CNetworkVehicle();
	bool HasDriver();
};

