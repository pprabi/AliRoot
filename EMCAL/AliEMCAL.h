#ifndef ALIEMCAL_H
#define ALIEMCAL_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice     */

/* $Id$ */

//_________________________________________________________________________
//  Base Class for EMCAL     
//                  
//*-- Author: Yves Schutz (SUBATECH)

// --- ROOT system ---

class TString ;
class TTask ;
class TFolder ;
class TRandom ; 

// --- AliRoot header files ---

#include "AliDetector.h"
#include "AliEMCALGeometry.h" 
class AliEMCAL : public AliDetector {

 public:

  AliEMCAL(); 
  AliEMCAL(const char* name, const char* title="");
  AliEMCAL(const AliEMCAL& emcal) : AliDetector(emcal) {
    // cpy ctor: no implementation yet
    // requested by the Coding Convention
    Fatal("cpy ctor", "not implemented") ;  
  }
  virtual ~AliEMCAL() ; 
  virtual void   AddHit(Int_t, Int_t*, Float_t *) const{
    Fatal("AddHit(Int_t, Int_t*, Float_t *", "not to be used: use AddHit( Int_t shunt, Int_t primary, Int_t track,Int_t id, Float_t *hits )") ;  
  }
  virtual void  Copy(AliEMCAL & emcal) ; 
  virtual AliDigitizer* CreateDigitizer(AliRunDigitizer* manager) const;
  virtual void  CreateMaterials() ;   
  virtual void  Digits2Raw();
  virtual void  FinishRun() {}                  
  virtual AliEMCALGeometry * GetGeometry() const 
  {return AliEMCALGeometry::GetInstance(GetTitle(),"") ;  }   
  virtual void    Hits2SDigits();
  virtual Int_t   IsVersion(void) const = 0 ;   
  Int_t GetRawFormatHighGainFactor() const { return fHighGainFactor ; }  
  Int_t GetRawFormatHighGainOffset() const { return fHighGainOffset ; }  
  Int_t GetRawFormatTimeBins() const { return fkTimeBins ; }    
  Double_t GetRawFormatTimeMax() const { return fTimeMax ; }   
  Double_t GetRawFormatTimePeak() const { return fTimePeak ; }    
  Double_t GetRawFormatTimeRes() const { return fTimeRes ; }   
  virtual AliLoader* MakeLoader(const char* topfoldername);
  static Double_t  RawResponseFunction(Double_t *x, Double_t *par) ; 
  virtual void SetTreeAddress() ;              
  virtual const TString Version() const {return TString(" ") ; }   
  AliEMCAL & operator = (const AliEMCAL & /*rvalue*/)  {
    Fatal("operator =", "not implemented") ;  return *this ; }
 
protected:

 Bool_t  RawSampledResponse(const Float_t dtime, const Int_t damp, Int_t * adcH, Int_t * adcL) const ; 

  Int_t fBirkC0;    // constants for Birk's Law implementation
  Double_t fBirkC1; // constants for Birk's Law implementation
  Double_t fBirkC2; // constants for Birk's Law implementation
  Int_t    fHighGainFactor ;   // High gain attenuation factor of the raw RO signal
  Int_t    fHighGainOffset ;   // offset added to the module id to distinguish high and low gain data
  static const Int_t fkTimeBins = 256 ;     // number of sampling bins of the raw RO signal  
  Double_t fTimeMax ;          // maximum sampled time of the raw RO signal
  Double_t fTimePeak ;         // peaking time of the raw RO signal
  Double_t fTimeRes ;          // decay rime width of the raw RO signal 

  ClassDef(AliEMCAL,8) // Electromagnetic calorimeter (base class)

} ;

#endif // ALIEMCAL_H
