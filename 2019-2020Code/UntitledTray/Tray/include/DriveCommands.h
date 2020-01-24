double getDriveFL();
double getDriveFR();
double getDriveBL();
double getDriveBR();
double getDriveR();
double getDriveL();
double getDriveF();
double getDriveB();
double getDrive();
void driveReset();
double getHeatFL();
double getHeatFR();
double getHeatBL();
double getHeatBR();
void setDrive(double lSpeed, double rSpeed);
void setDriveFull(double flSpeed, double blSpeed, double frSpeed, double brSpeed);
int driveEncoder(int dir, double speed, double dist);
int turnEncoder(int dir, double speed, double dist);
int strafeEncoder(int dir, double speed, double dist);
void setFL(double speed);
void setFR(double speed);
void setBL(double speed);
void setBR(double speed);
void driveBrake();
void driveCoast();
void driveStraight(int dir, double speed, double dist);
void driveTurn(int dir, double speed, double dist);
void driveStrafe(int dir, double speed, double dist);
int goP(int dir, double speed, double dist, double maxError);
int turnP(int dir, double speed, double dist, double maxError);