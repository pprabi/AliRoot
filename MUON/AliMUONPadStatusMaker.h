#ifndef ALIMUONPADSTATUSMAKER_H
#define ALIMUONPADSTATUSMAKER_H

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
* See cxx source for full Copyright notice                               */

// $Id$

/// \ingroup rec
/// \class AliMUONPadStatusMaker
/// \brief Make a 2DStore of pad statuses, using different sources of information
/// 
//  Author Laurent Aphecetche

#ifndef ROOT_TObject
#  include "TObject.h"
#endif
#ifndef ROOT_TVector2
#  include "TVector2.h"
#endif

class TExMap;
class AliMUONCalibrationData;
class AliMUONVCalibParam;
class AliMUONVTrackerData;
class AliMUONVStore;

class AliMUONPadStatusMaker : public TObject
{
public:
  AliMUONPadStatusMaker(const AliMUONCalibrationData& calibData);
  virtual ~AliMUONPadStatusMaker();
      
  /** Get access to internal status store (for debug only, as it may not be complete,
    depending on whether you've already called PadStatus for all possible de,manu
    combinations or not...
    */
  AliMUONVStore* StatusStore() const { return fStatus; }

  AliMUONVCalibParam* PadStatus(Int_t detElemId, Int_t manuId) const;

  Int_t PadStatus(Int_t detElemId, Int_t manuId, Int_t manuChannel) const;
  
  AliMUONVStore* NeighboursStore() const;
  
  AliMUONVCalibParam* Neighbours(Int_t detElemId, Int_t manuId) const;
  
  static TString AsString(Int_t status);

  static TString AsCondition(Int_t status);

  /// Return Low and High limits for a0 parameter of gain (linear slope)
  TVector2 GainA1Limits() const { return fGainA1Limits; }
  /// Return Low and High limits for a1 parameter of gain (parabolic term)
  TVector2 GainA2Limits() const { return fGainA2Limits; }
  /// Return Low and High limits for thres parameter of gain
  TVector2 GainThresLimits() const { return fGainThresLimits; }
  
  /// Return Low and High threshold for St12 HV
  TVector2 HVSt12Limits() const { return fHVSt12Limits; }
  /// Return Low and High threshold for St345 HV
  TVector2 HVSt345Limits() const { return fHVSt345Limits; }
  
  /// Return Low and High threshold for pedestal mean
  TVector2 PedMeanLimits() const { return fPedMeanLimits; }
  /// Return Low and High threshold for pedestal sigma
  TVector2 PedSigmaLimits() const { return fPedSigmaLimits; }
  
  /// Set Low and High limits for a0 parameter of gain (linear slope)
  void GainA1Limits(float low, float high) { fGainA1Limits.Set(low,high); }
  /// Set Low and High limits for a1 parameter of gain (parabolic term)
  void GainA2Limits(float low, float high) { fGainA2Limits.Set(low,high); }
  /// Set Low and High limits for thres parameter of gain
  void GainThresLimits(float low, float high) { fGainThresLimits.Set(low,high); }
  
  /// Set Low and High threshold for St12 HV
  void SetHVSt12Limits(float low, float high) { fHVSt12Limits.Set(low,high); }
  /// Set Low and High threshold for St345 HV
  void SetHVSt345Limits(float low, float high) { fHVSt345Limits.Set(low,high); }

  /// Set Low and High threshold for pedestal mean
  void SetPedMeanLimits(float low, float high) { fPedMeanLimits.Set(low,high); }
  /// Set Low and High threshold for pedestal sigma 
  void SetPedSigmaLimits(float low, float high) { fPedSigmaLimits.Set(low,high); }
  
	/// Set Low and High threshold for gain a0 term
	void SetGainA1Limits(float low, float high) { fGainA1Limits.Set(low,high); }
	/// Set Low and High threshold for gain a1 term
	void SetGainA2Limits(float low, float high) { fGainA2Limits.Set(low,high); }
	/// Set Low and High threshold for gain threshold term
	void SetGainThresLimits(float low, float high) { fGainThresLimits.Set(low,high); }
	
  /// Set Low and High manu occupancy limits
  void SetManuOccupancyLimits(float low, float high) { fManuOccupancyLimits.Set(low,high); }
  /// Get manu occupancy limits
  TVector2 ManuOccupancyLimits() const { return fManuOccupancyLimits; }
  
private:
  /// Not implemented
  AliMUONPadStatusMaker(const AliMUONPadStatusMaker&);
  /// Not implemented
  AliMUONPadStatusMaker& operator=(const AliMUONPadStatusMaker&);

  static void DecodeStatus(Int_t status, Int_t& pedStatus, Int_t& hvStatus, 
                           Int_t&  gainStatus, Int_t& otherStatus);
  static Int_t BuildStatus(Int_t pedStatus, Int_t hvStatus, 
                           Int_t gainStatus, Int_t otherStatus);
  
  AliMUONVCalibParam* ComputeStatus(Int_t detElemId, Int_t manuId) const;

  Bool_t HVSt12Status(Int_t detElemId, Int_t sector,
                      Bool_t& hvChannelTooLow,
                      Bool_t& hvChannelTooHigh,
                      Bool_t& hvChannelON) const;
  
  
  Bool_t HVSt345Status(Int_t detElemId, Int_t pcbIndex,
                       Bool_t& hvChannelTooLow,
                       Bool_t& hvChannelTooHigh,
                       Bool_t& hvChannelON,
                       Bool_t& hvSwitchON) const;

  Int_t HVStatus(Int_t detElemId, Int_t manuId) const;

  Int_t OtherStatus(Int_t detElemId, Int_t manuId) const;
  
  void SetHVStatus(Int_t detElemId, Int_t index, Int_t status) const;

private:
  /// General status
  enum EGeneralStatus
  {
    kMissing = (1<<7)
  };

  /// Gain status
  enum EGainStatus
  {
    kGainOK = 0,
    kGainA1TooLow = (1<<1),
    kGainA1TooHigh = (1<<2),
    kGainA2TooLow = (1<<3),
    kGainA2TooHigh = (1<<4),
    kGainThresTooLow = (1<<5),
    kGainThresTooHigh = (1<<6),
    
    kGainMissing = kMissing // please always use last bit for meaning "missing"
  };
  
  /// Pedestal status
  enum EPedestalStatus
  {
    kPedOK = 0,
    kPedMeanZero = (1<<1),
    kPedMeanTooLow = (1<<2),
    kPedMeanTooHigh = (1<<3),
    kPedSigmaTooLow = (1<<4),
    kPedSigmaTooHigh = (1<<5),
    
    kPedMissing = kMissing // please always use last bit for meaning "missing"
  };
  
  /// HV Error
  enum EHVError 
  {
    kHVOK = 0,
    kHVError = (1<<0),
    kHVTooLow = (1<<1),
    kHVTooHigh = (1<<2),
    kHVChannelOFF = (1<<3),
    kHVSwitchOFF = (1<<4),

    kHVMissing = kMissing // please always use last bit for meaning "missing"
  };
  
  /// Other
  enum EOtherStatus
  {
    kManuOccupancyTooLow = (1<<1),
    kManuOccupancyTooHigh = (1<<2)
  };
  
  const AliMUONCalibrationData& fkCalibrationData; //!< helper class to get data access (not owner)
  
  TVector2 fGainA1Limits; //!< Low and High threshold for gain a0 parameter
  TVector2 fGainA2Limits; //!< Low and High threshold for gain a1 parameter
  TVector2 fGainThresLimits; //!< Low and High threshold for gain threshold parameter

  TVector2 fHVSt12Limits; //!< Low and High threshold for St12 HV
  TVector2 fHVSt345Limits; //!< Low and High threshold for St345 HV

  TVector2 fPedMeanLimits; //!< Low and High threshold for pedestal mean
  TVector2 fPedSigmaLimits; //!< Low and High threshold for pedestal sigma
  
  TVector2 fManuOccupancyLimits; //!< Low and High manu occupancy limits
  
  AliMUONVStore* fStatus; //!< statuses of the pads
  
  mutable TExMap* fHV; //!< cache of hv statuses

  AliMUONVStore* fPedestals; //!< pedestal values
  AliMUONVStore* fGains; //!< gain values
  
  AliMUONVTrackerData* fTrackerData; //!< to get occupancies...
  
  ClassDef(AliMUONPadStatusMaker,0) // Creates pad statuses from ped,gain,hv
};

#endif
