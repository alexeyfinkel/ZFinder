#include "ZFinder/Event/interface/ZFinderPlotter.h"

// Standard Library
#include <string>  // string

// Root
#include <TCanvas.h>  // TCanvas

// ZFinder Code
#include "ZFinder/Event/interface/ZFinderElectron.h"  // ZFinderElectron


namespace zf {
    // Constructor
    ZFinderPlotter::ZFinderPlotter(TFileDirectory& tdir, const bool USE_MC) : USE_MC_(USE_MC) {
        /*
         * Initialize a set of histograms and associate them with a given TDirectory.
         */

        // Set up histograms
        // z0_mass_coarse_
        const std::string z0_mass_all_name = "Z0 Mass: All";
        z0_mass_all_ = tdir.make<TH1D>(z0_mass_all_name.c_str(), z0_mass_all_name.c_str(), 300, 0., 300.);
        z0_mass_all_->GetXaxis()->SetTitle("m_{ee} [GeV]");
        z0_mass_all_->GetYaxis()->SetTitle("Counts / GeV");

        // z0_mass_coarse_
        const std::string z0_mass_coarse_name = "Z0 Mass: Coarse";
        z0_mass_coarse_ = tdir.make<TH1D>(z0_mass_coarse_name.c_str(), z0_mass_coarse_name.c_str(), 100, 50., 150.);
        z0_mass_coarse_->GetXaxis()->SetTitle("m_{ee} [GeV]");
        z0_mass_coarse_->GetYaxis()->SetTitle("Counts / GeV");

        // z0_mass_fine_
        const std::string z0_mass_fine_name = "Z0 Mass: Fine";
        z0_mass_fine_ = tdir.make<TH1D>(z0_mass_fine_name.c_str(), z0_mass_fine_name.c_str(), 80, 80., 100.);
        z0_mass_fine_->GetXaxis()->SetTitle("m_{ee} [GeV]");
        z0_mass_fine_->GetYaxis()->SetTitle("Counts / 0.25 GeV");

        // z0_rapidity_
        const std::string z0_rapidity_name = "Z0 Rapidity";
        z0_rapidity_ = tdir.make<TH1D>(z0_rapidity_name.c_str(), z0_rapidity_name.c_str(), 100, -5., 5.);
        z0_rapidity_->GetXaxis()->SetTitle("Z_{Y}");
        z0_rapidity_->GetYaxis()->SetTitle("Counts");

        // z0_pt
        const std::string z0_pt_name = "Z0 p_{T}";
        z0_pt_ = tdir.make<TH1D>(z0_pt_name.c_str(), z0_pt_name.c_str(), 200, 0., 200.);
        z0_pt_->GetXaxis()->SetTitle("p_{T,Z}");
        z0_pt_->GetYaxis()->SetTitle("Counts / GeV");

        // e0_pt
        const std::string e0_pt_name = "p_{T,e_{0}}";
        e0_pt_ = tdir.make<TH1D>(e0_pt_name.c_str(), e0_pt_name.c_str(), 200, 0., 200.);
        e0_pt_->GetXaxis()->SetTitle("p_{T,e_{0}}");
        e0_pt_->GetYaxis()->SetTitle("Counts / GeV");

        // e1_pt
        const std::string e1_pt_name = "p_{T,e_{1}}";
        e1_pt_ = tdir.make<TH1D>(e1_pt_name.c_str(), e1_pt_name.c_str(), 200, 0., 200.);
        e1_pt_->GetXaxis()->SetTitle("p_{T,e_{0}}");
        e1_pt_->GetYaxis()->SetTitle("Counts / GeV");

        // e0_eta_
        const std::string e0_eta_name = "#eta_{e_{0}}";
        e0_eta_ = tdir.make<TH1D>(e0_eta_name.c_str(), e0_eta_name.c_str(), 50, -5., 5.);
        e0_eta_->GetXaxis()->SetTitle("#eta_{e_{0}}");
        e0_eta_->GetYaxis()->SetTitle("Counts");

        // e1_eta_
        const std::string e1_eta_name = "#eta_{e_{1}}";
        e1_eta_ = tdir.make<TH1D>(e1_eta_name.c_str(), e1_eta_name.c_str(), 50, -5., 5.);
        e1_eta_->GetXaxis()->SetTitle("#eta_{e_{1}}");
        e1_eta_->GetYaxis()->SetTitle("Counts");

        // e0_phi_
        const std::string e0_phi_name = "#phi_{e_{0}}";
        e0_phi_ = tdir.make<TH1D>(e0_phi_name.c_str(), e0_phi_name.c_str(), 60, -3.15, 3.15);
        e0_phi_->GetXaxis()->SetTitle("#phi_{e_{0}}");
        e0_phi_->GetYaxis()->SetTitle("Counts");

        // e1_phi_
        const std::string e1_phi_name = "#phi_{e_{1}}";
        e1_phi_ = tdir.make<TH1D>(e1_phi_name.c_str(), e1_phi_name.c_str(), 50, -3.15, 3.15);
        e1_phi_->GetXaxis()->SetTitle("#phi_{e_{1}}");
        e1_phi_->GetYaxis()->SetTitle("counts");

        // e0_charge_
        const std::string e0_charge_name = "charge_{e_{0}}";
        e0_charge_ = tdir.make<TH1D>(e0_charge_name.c_str(), e0_charge_name.c_str(), 60, -3.15, 3.15);
        e0_charge_->GetXaxis()->SetTitle("charge_{e_{0}}");
        e0_charge_->GetYaxis()->SetTitle("Counts");

        // e1_charge_
        const std::string e1_charge_name = "charge_{e_{1}}";
        e1_charge_ = tdir.make<TH1D>(e1_charge_name.c_str(), e1_charge_name.c_str(), 50, -3.15, 3.15);
        e1_charge_->GetXaxis()->SetTitle("charge_{e_{1}}");
        e1_charge_->GetYaxis()->SetTitle("counts");

        // phistar
        const std::string phistar_name = "#phi*";
        phistar_ = tdir.make<TH1D>(phistar_name.c_str(), phistar_name.c_str(), 4000, 0., 4.);
        phistar_->GetXaxis()->SetTitle("#phi*");
        phistar_->GetYaxis()->SetTitle("Counts");

        // other_phistar for gen-reco efficiencies
        const std::string other_phistar_name = "Other #phi*";
        other_phistar_ = tdir.make<TH1D>(other_phistar_name.c_str(), other_phistar_name.c_str(), 4000, 0., 4.);
        other_phistar_->GetXaxis()->SetTitle("#phi*_{other}");
        other_phistar_->GetYaxis()->SetTitle("Counts");

        // other_y_ for gen-reco efficiencies
        const std::string other_y_name = "Other Rapidity";
        other_y_ = tdir.make<TH1D>(other_y_name.c_str(), other_y_name.c_str(), 100, -5., 5.);
        other_y_->GetXaxis()->SetTitle("Z_{Y, other}");
        other_y_->GetYaxis()->SetTitle("Counts");

        // pileup
        const std::string pileup_name = "N_{Vertices}";
        pileup_ = tdir.make<TH1D>(pileup_name.c_str(), pileup_name.c_str(), 100, 0., 100.);
        pileup_->GetXaxis()->SetTitle("Number of Vertices");
        pileup_->GetYaxis()->SetTitle("Counts");

        // nelectrons
        const std::string nelectrons_name = "N_{e}";
        nelectrons_ = tdir.make<TH1D>(nelectrons_name.c_str(), nelectrons_name.c_str(), 10, 0., 10.);
        nelectrons_->GetXaxis()->SetTitle("N_{e}");
        nelectrons_->GetYaxis()->SetTitle("Events");

        // baseweights
        const std::string baseweights_name = "Base Weight";
        baseweights_ = tdir.make<TH1D>(baseweights_name.c_str(), baseweights_name.c_str(), 500, 0., 5.);
        baseweights_->GetXaxis()->SetTitle("Weight");
        baseweights_->GetYaxis()->SetTitle("Events");

        // fullweights
        const std::string fullweights_name = "Full Weight";
        fullweights_ = tdir.make<TH1D>(fullweights_name.c_str(), fullweights_name.c_str(), 500, 0., 5.);
        fullweights_->GetXaxis()->SetTitle("Weight");
        fullweights_->GetYaxis()->SetTitle("Events");

        // e0_pt_vs_trig
        const std::string e0_pt_vs_trig_name = "p_{T,e_{0}} Vs. Trigger";
        e0_pt_vs_trig_ = tdir.make<TH1D>(e0_pt_vs_trig_name.c_str(), e0_pt_vs_trig_name.c_str(), 200, 0., 2.);
        e0_pt_vs_trig_->GetXaxis()->SetTitle("Ratio of p_{T,e_{0}} Reco / Trigger");
        e0_pt_vs_trig_->GetYaxis()->SetTitle("Events");

        // e1_pt_vs_trig
        const std::string e1_pt_vs_trig_name = "p_{T,e_{1}} Vs. Trigger";
        e1_pt_vs_trig_ = tdir.make<TH1D>(e1_pt_vs_trig_name.c_str(), e1_pt_vs_trig_name.c_str(), 200, 0., 2.);
        e1_pt_vs_trig_->GetXaxis()->SetTitle("Ratio of p_{T,e_{1}} Reco / Trigger");
        e1_pt_vs_trig_->GetYaxis()->SetTitle("Events");

        // phistar
        const std::string phistar_vs_truth_name = "#phi*: Reco Vs. Truth";
        phistar_vs_truth_ = tdir.make<TH1D>(phistar_vs_truth_name.c_str(), phistar_vs_truth_name.c_str(), 200, 0., 2.);
		phistar_vs_truth_->GetXaxis()->SetTitle("#phi* Reco MC / Truth");
        phistar_vs_truth_->GetYaxis()->SetTitle("Events");

        //deltaR
        const std::string deltaR_name = "#DeltaR";
        deltaR_ = tdir.make<TH1D>(deltaR_name.c_str(), deltaR_name.c_str(), 100, 0., 10.);
        deltaR_->GetXaxis()->SetTitle("#DeltaR(e_{0},e_{1})");
        deltaR_->GetYaxis()->SetTitle("Counts");
    }

    void ZFinderPlotter::Fill(
            const ZFinderEvent& ZF_EVENT,
            const int ELECTRON_0,
            const int ELECTRON_1,
            const double EVENT_WEIGHT
            ) {
        /*
         * Given a zf_event, fills all the histograms.
         *
         * ELECTRON_0 and ELECTRON_1 can be used to assign zf_event.eN to the given
         * number in the histogram. For example, assigning ELECTRON_0 = 1 will fill
         * the e0 histograms with data from zf_event.e1.
         */
        // Z Info
        if (!USE_MC_) {
            z0_mass_all_->Fill(ZF_EVENT.reco_z.m, EVENT_WEIGHT);
            z0_mass_coarse_->Fill(ZF_EVENT.reco_z.m, EVENT_WEIGHT);
            z0_mass_fine_->Fill(ZF_EVENT.reco_z.m, EVENT_WEIGHT);
            z0_rapidity_->Fill(ZF_EVENT.reco_z.y, EVENT_WEIGHT);
            z0_pt_->Fill(ZF_EVENT.reco_z.pt, EVENT_WEIGHT);
            phistar_->Fill(ZF_EVENT.reco_z.phistar, EVENT_WEIGHT);
            deltaR_->Fill(ZF_EVENT.reco_z.deltaR, EVENT_WEIGHT);
            // We only want to plot this if corresponding gen info exists
            if(!ZF_EVENT.is_real_data) {
                other_phistar_->Fill(ZF_EVENT.reco_z.other_phistar, EVENT_WEIGHT);
                other_y_->Fill(ZF_EVENT.reco_z.other_y, EVENT_WEIGHT);
            }

            // Fill the histograms with the information from the approriate electron
            if (ELECTRON_0 == 0 && ELECTRON_1 == 1) {
                if (ZF_EVENT.e0 != NULL) {
                    e0_pt_->Fill(ZF_EVENT.e0->pt, EVENT_WEIGHT);
                    e0_eta_->Fill(ZF_EVENT.e0->eta, EVENT_WEIGHT);
                    e0_phi_->Fill(ZF_EVENT.e0->phi, EVENT_WEIGHT);
                    e0_charge_->Fill(ZF_EVENT.e0->charge, EVENT_WEIGHT);
                }
                if (ZF_EVENT.e1 != NULL) {
                    e1_pt_->Fill(ZF_EVENT.e1->pt, EVENT_WEIGHT);
                    e1_eta_->Fill(ZF_EVENT.e1->eta, EVENT_WEIGHT);
                    e1_phi_->Fill(ZF_EVENT.e1->phi, EVENT_WEIGHT);
                    e1_charge_->Fill(ZF_EVENT.e1->charge, EVENT_WEIGHT);
                }
                if (ZF_EVENT.e0_trig != NULL && ZF_EVENT.e0 != NULL) {
                    e0_pt_vs_trig_->Fill(
                            ZF_EVENT.e0->pt / ZF_EVENT.e0_trig->pt,
                            EVENT_WEIGHT
                            );
                }
                if (ZF_EVENT.e1_trig != NULL && ZF_EVENT.e1 != NULL) {
                    e1_pt_vs_trig_->Fill(
                            ZF_EVENT.e1->pt / ZF_EVENT.e1_trig->pt,
                            EVENT_WEIGHT
                            );
                }
            }
            else if (ELECTRON_0 == 1 && ELECTRON_1 == 0) {
                if (ZF_EVENT.e1 != NULL) {
                    e0_pt_->Fill(ZF_EVENT.e1->pt, EVENT_WEIGHT);
                    e0_eta_->Fill(ZF_EVENT.e1->eta, EVENT_WEIGHT);
                    e0_phi_->Fill(ZF_EVENT.e1->phi, EVENT_WEIGHT);
                    e0_charge_->Fill(ZF_EVENT.e1->charge, EVENT_WEIGHT);
                }
                if (ZF_EVENT.e0 != NULL) {
                    e1_pt_->Fill(ZF_EVENT.e0->pt, EVENT_WEIGHT);
                    e1_eta_->Fill(ZF_EVENT.e0->eta, EVENT_WEIGHT);
                    e1_phi_->Fill(ZF_EVENT.e0->phi, EVENT_WEIGHT);
                    e1_charge_->Fill(ZF_EVENT.e0->charge, EVENT_WEIGHT);
                }
                if (ZF_EVENT.e1_trig != NULL && ZF_EVENT.e1 != NULL) {
                    e0_pt_vs_trig_->Fill(
                            ZF_EVENT.e1->pt / ZF_EVENT.e1_trig->pt,
                            EVENT_WEIGHT
                            );
                }
                if (ZF_EVENT.e0_trig != NULL && ZF_EVENT.e0 != NULL) {
                    e1_pt_vs_trig_->Fill(
                            ZF_EVENT.e0->pt / ZF_EVENT.e0_trig->pt,
                            EVENT_WEIGHT
                            );
                }
            }
            // Event Info
            pileup_->Fill(ZF_EVENT.reco_vert.num, EVENT_WEIGHT);
            nelectrons_->Fill(ZF_EVENT.n_reco_electrons, EVENT_WEIGHT);
        }
        else if (USE_MC_ && !ZF_EVENT.is_real_data) {
            z0_mass_all_->Fill(ZF_EVENT.truth_z.m, EVENT_WEIGHT);
            z0_mass_coarse_->Fill(ZF_EVENT.truth_z.m, EVENT_WEIGHT);
            z0_mass_fine_->Fill(ZF_EVENT.truth_z.m, EVENT_WEIGHT);
            z0_rapidity_->Fill(ZF_EVENT.truth_z.y, EVENT_WEIGHT);
            z0_pt_->Fill(ZF_EVENT.truth_z.pt, EVENT_WEIGHT);
            phistar_->Fill(ZF_EVENT.truth_z.phistar, EVENT_WEIGHT);
            deltaR_->Fill(ZF_EVENT.truth_z.deltaR, EVENT_WEIGHT);
            other_phistar_->Fill(ZF_EVENT.truth_z.other_phistar, EVENT_WEIGHT);
            other_y_->Fill(ZF_EVENT.truth_z.other_y, EVENT_WEIGHT);

            // Fill the histograms with the information from the approriate electron
            if (ELECTRON_0 == 0 && ELECTRON_1 == 1) {
                if (ZF_EVENT.e0_truth != NULL) {
                    e0_pt_->Fill(ZF_EVENT.e0_truth->pt, EVENT_WEIGHT);
                    e0_eta_->Fill(ZF_EVENT.e0_truth->eta, EVENT_WEIGHT);
                    e0_phi_->Fill(ZF_EVENT.e0_truth->phi, EVENT_WEIGHT);
                    e0_charge_->Fill(ZF_EVENT.e0_truth->charge, EVENT_WEIGHT);
                }
                if (ZF_EVENT.e1_truth != NULL) {
                    e1_pt_->Fill(ZF_EVENT.e1_truth->pt, EVENT_WEIGHT);
                    e1_eta_->Fill(ZF_EVENT.e1_truth->eta, EVENT_WEIGHT);
                    e1_phi_->Fill(ZF_EVENT.e1_truth->phi, EVENT_WEIGHT);
                    e1_charge_->Fill(ZF_EVENT.e1_truth->charge, EVENT_WEIGHT);
                }
                if (ZF_EVENT.e0_trig != NULL && ZF_EVENT.e0_truth != NULL) {
                    e0_pt_vs_trig_->Fill(
                            ZF_EVENT.e0_truth->pt / ZF_EVENT.e0_trig->pt,
                            EVENT_WEIGHT
                            );
                }
                if (ZF_EVENT.e1_trig != NULL && ZF_EVENT.e1_truth != NULL) {
                    e1_pt_vs_trig_->Fill(
                            ZF_EVENT.e1_truth->pt / ZF_EVENT.e1_trig->pt,
                            EVENT_WEIGHT
                            );
                }
            }
            else if (ELECTRON_0 == 1 && ELECTRON_1 == 0) {
                if (ZF_EVENT.e1_truth != NULL) {
                    e0_pt_->Fill(ZF_EVENT.e1_truth->pt, EVENT_WEIGHT);
                    e0_eta_->Fill(ZF_EVENT.e1_truth->eta, EVENT_WEIGHT);
                    e0_phi_->Fill(ZF_EVENT.e1_truth->phi, EVENT_WEIGHT);
                    e0_charge_->Fill(ZF_EVENT.e1_truth->charge, EVENT_WEIGHT);
                }
                if (ZF_EVENT.e0_truth != NULL) {
                    e1_pt_->Fill(ZF_EVENT.e0_truth->pt, EVENT_WEIGHT);
                    e1_eta_->Fill(ZF_EVENT.e0_truth->eta, EVENT_WEIGHT);
                    e1_phi_->Fill(ZF_EVENT.e0_truth->phi, EVENT_WEIGHT);
                    e1_charge_->Fill(ZF_EVENT.e0_truth->charge, EVENT_WEIGHT);
                }
                if (ZF_EVENT.e1_trig != NULL && ZF_EVENT.e1_truth != NULL) {
                    e0_pt_vs_trig_->Fill(
                            ZF_EVENT.e1_truth->pt / ZF_EVENT.e1_trig->pt,
                            EVENT_WEIGHT
                            );
                }
                if (ZF_EVENT.e0_trig != NULL && ZF_EVENT.e0_truth != NULL) {
                    e1_pt_vs_trig_->Fill(
                            ZF_EVENT.e0_truth->pt / ZF_EVENT.e0_trig->pt,
                            EVENT_WEIGHT
                            );
                }
            }
            // Event Info
            pileup_->Fill(ZF_EVENT.truth_vert.num, EVENT_WEIGHT);
            nelectrons_->Fill(2, EVENT_WEIGHT);  // We only ever grab the two electrons from the Z
        }
        // Event weights, they are of course, unweighted
        baseweights_->Fill(ZF_EVENT.event_weight);
        fullweights_->Fill(EVENT_WEIGHT);

        // Phistar Reco Vs. Truth
        if (!ZF_EVENT.is_real_data
                && ZF_EVENT.e0_truth != NULL
                && ZF_EVENT.e1_truth != NULL
                && ZF_EVENT.e0 != NULL
                && ZF_EVENT.e1 != NULL
           ) {
            phistar_vs_truth_->Fill(
                    ZF_EVENT.reco_z.phistar / ZF_EVENT.truth_z.phistar,
                    EVENT_WEIGHT
                    );
        }
    }
}  // namespace zf
