# ZNC AutoMode

## 📋 Description

AutoMode est un module ZNC qui automatise l'attribution de modes op et voice aux utilisateurs lors de leur arrivée sur un canal IRC. Il permet de maintenir automatiquement les privilèges sans intervention manuelle, avec une configuration persistante et des commandes simples.

- Type: Module ZNC (.so)
- Fonction: auto-op/voice basé sur masques configurables
- Persistance: configuration sauvegardée et rechargée au redémarrage

## ✨ Fonctionnalités

- Auto-Op ou Auto-Voice des utilisateurs rejoignant un canal
- Configuration simple via commandes privées (/msg)
- Persistance de la configuration entre redémarrages ZNC
- Gestion par canal (différentes règles par canal)
- Support des masques d'utilisateurs (nick!user@host)
- Activation/désactivation par canal

## 📦 Prérequis

- ZNC 1.6+ (ou version supérieure)
- Outils de compilation C++ (g++/clang avec support C++11)
- znc-buildmod (inclus dans le package znc-dev ou znc-devel selon la distribution)

## 🚀 Installation

1) Télécharger le module
```bash
git clone https://github.com/ZarTek-Creole/znc-automode.git
cd znc-automode
```

2) Compiler le module
```bash
znc-buildmod automode.cpp
```

3) Copier le module compilé dans le répertoire modules ZNC
```bash
# Répertoire global (root requis)
sudo cp automode.so /usr/lib/znc/
# OU répertoire utilisateur
cp automode.so ~/.znc/modules/
```

4) Charger le module
- Via webadmin: Settings → Your Settings → Modules → automode
- Via console IRC:
```
/msg *status LoadMod automode
```

## ⚙️ Configuration

Commandes disponibles via message privé au module:

```
# Ajouter un canal en mode auto-op
/msg *automode add #canal op

# Ajouter un canal en mode auto-voice
/msg *automode add #canal voice

# Supprimer un canal de la configuration
/msg *automode del #canal

# Lister tous les canaux configurés
/msg *automode list

# Aide (affiche toutes les commandes)
/msg *automode help
```

### Exemples d'utilisation

```
# Configurer auto-op sur #dev
/msg *automode add #dev op

# Configurer auto-voice sur #support
/msg *automode add #support voice

# Vérifier la configuration
/msg *automode list
# Résultat:
# #dev: op
# #support: voice

# Retirer #support
/msg *automode del #support
```

## 🔎 Dépannage

- **Module ne se charge pas**: vérifiez que automode.so est dans le bon répertoire modules de ZNC
- **Compilation échoue**: assurez-vous que znc-dev/znc-devel est installé
- **Modes non appliqués**: vérifiez que le bot a les permissions op sur le canal
- **Config perdue au redémarrage**: contrôlez les permissions d'écriture sur ~/.znc/moddata/automode/

## 🤝 Contribution

Les contributions sont les bienvenues!

1. Fork du projet
2. Création d'une branche feature (`git checkout -b feature/amelioration`)
3. Commit des changements (`git commit -m 'Ajout d'une fonctionnalité'`)
4. Push vers la branche (`git push origin feature/amelioration`)
5. Ouverture d'une Pull Request

## 📝 Licence

Ce projet est sous licence **GPL-3.0**. Voir le fichier [LICENSE](LICENSE) pour les détails complets.

## 👤 Auteur

**ZarTek-Creole**
- GitHub: [@ZarTek-Creole](https://github.com/ZarTek-Creole)
- Projet: [znc-automode](https://github.com/ZarTek-Creole/znc-automode)

## 🐛 Support

Pour signaler un bug ou demander une fonctionnalité, ouvrez une [issue](https://github.com/ZarTek-Creole/znc-automode/issues) sur GitHub.

## 📚 Ressources

- [Documentation ZNC](https://wiki.znc.in/)
- [Guide de développement de modules ZNC](https://wiki.znc.in/Writing_modules)
- [API ZNC (C++)](https://znc.in/docs/api/)
