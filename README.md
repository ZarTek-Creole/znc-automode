# ZNC AutoMode Module

Un module ZNC simple pour l'auto-op/voice sur les canaux IRC.

## Fonctionnalités

- Auto-Op ou Auto-Voice des utilisateurs qui rejoignent un canal
- Configuration simple via commandes privées
- Persistance de la configuration

## Installation

1. Téléchargez le fichier `automode.cpp`
2. Compilez-le:
   ```bash
   znc-buildmod automode.cpp
   ```
3. Copiez le fichier résultant `automode.so` dans votre dossier de modules ZNC
4. Chargez le module:
   - Via la webadmin
   - Ou en console: `/msg *status LoadMod automode`

## Utilisation

Commandes disponibles via message privé au bot:

```
/msg *automode add #canal op       # Ajoute un canal en auto-op
/msg *automode add #canal voice    # Ajoute un canal en auto-voice
/msg *automode del #canal          # Supprime un canal
/msg *automode list                # Liste les canaux configurés
```

## Auteur

- **ZarTek-Creole** - Développeur principal  
  GitHub: [https://github.com/ZarTek-Creole](https://github.com/ZarTek-Creole)

## License

Ce projet est sous licence GPLv3 - voir le fichier [LICENSE](LICENSE) pour plus de détails.

## Contribuer

Les contributions sont les bienvenues! Ouvrez une issue ou une pull request sur GitHub.

## Support

Si vous rencontrez des problèmes, ouvrez une issue sur GitHub.