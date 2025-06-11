/*
 * automode.cpp - Module ZNC pour l'auto-op/voice sur les canaux
 *
 * Copyright (C) 2025 ZarTek-Creole
 * 
 * Ce programme est un module pour ZNC qui permet de configurer 
 * l'auto-op ou auto-voice sur des canaux spécifiques.
 *
 * Voir https://github.com/ZarTek-Creole/znc-automode pour documentation
 *
 * License: GPLv3
 *
 * Fonctionnalités:
 * - /msg *automode add #channel op|voice
 * - /msg *automode del #channel
 * - /msg *automode list
 */

#include <znc/IRCNetwork.h>
#include <znc/Chan.h>

using std::vector;

class CAutoModeMod : public CModule {
  public:
    MODCONSTRUCTOR(CAutoModeMod) {
        AddHelpCommand();
        AddCommand("Add", t_d("<channel> <op|voice>"), 
                  t_d("Ajoute un canal avec le mode désiré"),
                  [=](const CString& sLine) { OnAddCommand(sLine); });
        AddCommand("Del", t_d("<channel>"), 
                  t_d("Supprime un canal de la liste"),
                  [=](const CString& sLine) { OnDelCommand(sLine); });
        AddCommand("List", "", 
                  t_d("Liste tous les canaux configurés"),
                  [=](const CString& sLine) { OnListCommand(sLine); });
    }

    bool OnLoad(const CString& sArgs, CString& sMessage) override {
        // Charger la configuration existante
        for (MCString::iterator it = BeginNV(); it != EndNV(); ++it) {
            const CString& sChan = it->first;
            const CString& sMode = it->second;
            m_mChannels[sChan.AsLower()] = sMode;
        }
        return true;
    }

    void OnJoin(const CNick& Nick, CChan& Channel) override {
        // Si on a les droits sur ce canal
        if (Channel.HasPerm(CChan::Op)) {
            ApplyAutoMode(Nick, Channel);
        }
    }

    void OnAddCommand(const CString& sLine) {
        CString sChan = sLine.Token(1);
        CString sMode = sLine.Token(2).AsLower();

        if (sChan.empty() || (sMode != "op" && sMode != "voice")) {
            PutModule("Usage: add <channel> <op|voice>");
            return;
        }

        m_mChannels[sChan.AsLower()] = sMode;
        SetNV(sChan, sMode);
        PutModule("Canal " + sChan + " ajouté avec mode " + sMode);
    }

    void OnDelCommand(const CString& sLine) {
        CString sChan = sLine.Token(1);

        if (sChan.empty()) {
            PutModule("Usage: del <channel>");
            return;
        }

        if (m_mChannels.erase(sChan.AsLower())) {
            DelNV(sChan);
            PutModule("Canal " + sChan + " supprimé");
        } else {
            PutModule("Canal " + sChan + " non trouvé");
        }
    }

    void OnListCommand(const CString& sLine) {
        if (m_mChannels.empty()) {
            PutModule("Aucun canal configuré");
            return;
        }

        CTable Table;
        Table.AddColumn("Canal");
        Table.AddColumn("Mode");

        for (const auto& it : m_mChannels) {
            Table.AddRow();
            Table.SetCell("Canal", it.first);
            Table.SetCell("Mode", it.second);
        }

        PutModule(Table);
    }

    void ApplyAutoMode(const CNick& Nick, CChan& Channel) {
        CString sChan = Channel.GetName().AsLower();
        auto it = m_mChannels.find(sChan);
        
        if (it != m_mChannels.end()) {
            CString sMode = it->second;
            if (sMode == "op") {
                PutIRC("MODE " + Channel.GetName() + " +o " + Nick.GetNick());
            } else if (sMode == "voice") {
                PutIRC("MODE " + Channel.GetName() + " +v " + Nick.GetNick());
            }
        }
    }

  private:
    std::map<CString, CString> m_mChannels; // canal -> mode (op/voice)
};

template <>
void TModInfo<CAutoModeMod>(CModInfo& Info) {
    Info.SetWikiPage("automode");
    Info.SetHasArgs(false);
    Info.SetArgsHelpText("Pas d'arguments nécessaires");
}

NETWORKMODULEDEFS(CAutoModeMod, t_s("Auto-op/voice sur les canaux configurés"))